/****************************************************************************
**
** Copyright (C) 2016 Tim Sander <tim@krieglstein.org>
** Copyright (C) 2016 Denis Shienkov <denis.shienkov@gmail.com>
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

#include "baremetaldevice.h"
#include "baremetaldeviceconfigurationwidget.h"

#include "gdbserverprovider.h"
#include "gdbserverproviderchooser.h"

#include <utils/pathchooser.h>
#include <utils/qtcassert.h>

#include <QFormLayout>

namespace BareMetal {
namespace Internal {

// BareMetalDeviceConfigurationWidget

BareMetalDeviceConfigurationWidget::BareMetalDeviceConfigurationWidget(
        const ProjectExplorer::IDevice::Ptr &deviceConfig)
    : IDeviceWidget(deviceConfig)
{
    const auto dev = qSharedPointerCast<const BareMetalDevice>(device());
    QTC_ASSERT(dev, return);

    const auto formLayout = new QFormLayout(this);
    formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);

    m_gdbServerProviderChooser = new GdbServerProviderChooser(true, this);
    m_gdbServerProviderChooser->populate();
    m_gdbServerProviderChooser->setCurrentProviderId(dev->gdbServerProviderId());
    formLayout->addRow(tr("GDB server provider:"), m_gdbServerProviderChooser);

    connect(m_gdbServerProviderChooser, &GdbServerProviderChooser::providerChanged,
            this, &BareMetalDeviceConfigurationWidget::gdbServerProviderChanged);

    m_peripheralDescriptionFileChooser = new Utils::PathChooser(this);
    m_peripheralDescriptionFileChooser->setExpectedKind(Utils::PathChooser::File);
    m_peripheralDescriptionFileChooser->setPromptDialogFilter(
                tr("Peripheral description files (*.svd)"));
    m_peripheralDescriptionFileChooser->setPromptDialogTitle(
                tr("Select Peripheral Description File"));
    m_peripheralDescriptionFileChooser->setPath(dev->peripheralDescriptionFilePath());
    formLayout->addRow(tr("Peripheral description file:"),
                       m_peripheralDescriptionFileChooser);

    connect(m_peripheralDescriptionFileChooser, &Utils::PathChooser::pathChanged,
            this, &BareMetalDeviceConfigurationWidget::peripheralDescriptionFileChanged);
}

void BareMetalDeviceConfigurationWidget::gdbServerProviderChanged()
{
    const auto dev = qSharedPointerCast<BareMetalDevice>(device());
    QTC_ASSERT(dev, return);
    dev->setGdbServerProviderId(m_gdbServerProviderChooser->currentProviderId());
}

void BareMetalDeviceConfigurationWidget::peripheralDescriptionFileChanged()
{
    const auto dev = qSharedPointerCast<BareMetalDevice>(device());
    QTC_ASSERT(dev, return);
    dev->setPeripheralDescriptionFilePath(m_peripheralDescriptionFileChooser->path());
}

void BareMetalDeviceConfigurationWidget::updateDeviceFromUi()
{
    gdbServerProviderChanged();
}

} // namespace Internal
} // namespace BareMetal
