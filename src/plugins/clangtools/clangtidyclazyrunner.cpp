/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#include "clangtidyclazyrunner.h"

#include "clangtoolssettings.h"
#include "clangtoolsutils.h"

#include <coreplugin/icore.h>

#include <cpptools/clangdiagnosticconfigsmodel.h>
#include <cpptools/compileroptionsbuilder.h>
#include <cpptools/cpptoolsreuse.h>

#include <utils/synchronousprocess.h>
#include <utils/qtcassert.h>

#include <QDebug>
#include <QDir>
#include <QLoggingCategory>

static Q_LOGGING_CATEGORY(LOG, "qtc.clangtools.runner", QtWarningMsg)

using namespace CppTools;

namespace ClangTools {
namespace Internal {

static QStringList serializeDiagnosticsArguments(const QStringList &baseOptions,
                                                 const QString &outputFilePath)
{
    const QStringList serializeArgs{"-serialize-diagnostics", outputFilePath};
    if (baseOptions.contains("--driver-mode=cl"))
        return clangArgsForCl(serializeArgs);
    return serializeArgs;
}

static QStringList clazyPluginArguments(const ClangDiagnosticConfig diagnosticConfig)
{
    QStringList arguments;

    const QString clazyChecks = diagnosticConfig.clazyChecks();
    if (!clazyChecks.isEmpty()) {
        arguments << XclangArgs({"-add-plugin",
                                 "clazy",
                                 "-plugin-arg-clazy",
                                 diagnosticConfig.clazyChecks()});
    }

    return arguments;
}

static QStringList tidyChecksArguments(const ClangDiagnosticConfig diagnosticConfig)
{
    const ClangDiagnosticConfig::TidyMode tidyMode = diagnosticConfig.clangTidyMode();
    if (tidyMode != ClangDiagnosticConfig::TidyMode::Disabled) {
        if (tidyMode != ClangDiagnosticConfig::TidyMode::File)
            return {"-checks=" + diagnosticConfig.clangTidyChecks()};
    }

    return {};
}

static QStringList clazyChecksArguments(const ClangDiagnosticConfig diagnosticConfig)
{
    const QString clazyChecks = diagnosticConfig.clazyChecks();
    if (!clazyChecks.isEmpty())
        return {"-checks=" + diagnosticConfig.clazyChecks()};
    return {};
}

static QStringList mainToolArguments(const QString &mainFilePath, const QString &outputFilePath)
{
    return {
        "-export-fixes=" + outputFilePath,
        QDir::toNativeSeparators(mainFilePath),
    };
}

static QStringList clangArguments(const ClangDiagnosticConfig &diagnosticConfig,
                                  const QStringList &baseOptions)
{
    QStringList arguments;
    arguments << ClangDiagnosticConfigsModel::globalDiagnosticOptions()
              << diagnosticConfig.clangOptions()
              << baseOptions;

    if (LOG().isDebugEnabled())
        arguments << QLatin1String("-v");

    return arguments;
}

ClangTidyRunner::ClangTidyRunner(const ClangDiagnosticConfig &config, QObject *parent)
    : ClangToolRunner(parent)
{
    setName(tr("Clang-Tidy"));
    setOutputFileFormat(OutputFileFormat::Yaml);
    setExecutable(clangTidyExecutable());
    setArgsCreator([this, config](const QStringList &baseOptions) {
        return QStringList()
            << tidyChecksArguments(config)
            << mainToolArguments(fileToAnalyze(), outputFilePath())
            << "--"
            << clangArguments(config, baseOptions);
    });
}

ClazyStandaloneRunner::ClazyStandaloneRunner(const ClangDiagnosticConfig &config, QObject *parent)
    : ClangToolRunner(parent)
{
    setName(tr("Clazy"));
    setOutputFileFormat(OutputFileFormat::Yaml);
    setExecutable(clazyStandaloneExecutable());
    setArgsCreator([this, config](const QStringList &baseOptions) {
        return QStringList()
            << clazyChecksArguments(config)
            << mainToolArguments(fileToAnalyze(), outputFilePath())
            << "--"
            << clangArguments(config, baseOptions);
    });
}

ClazyPluginRunner::ClazyPluginRunner(const ClangDiagnosticConfig &config, QObject *parent)
    : ClangToolRunner(parent)
{
    setName(tr("Clazy"));
    setOutputFileFormat(OutputFileFormat::Serialized);
    setExecutable(Core::ICore::clangExecutable(CLANG_BINDIR));
    setArgsCreator([this, config](const QStringList &baseOptions) {
        return serializeDiagnosticsArguments(baseOptions, outputFilePath())
            << clazyPluginArguments(config)
            << clangArguments(config, baseOptions)
            << QDir::toNativeSeparators(fileToAnalyze());
    });
}

} // namespace Internal
} // namespace ClangTools
