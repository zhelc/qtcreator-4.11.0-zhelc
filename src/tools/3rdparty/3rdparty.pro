TEMPLATE = subdirs
isEmpty(BUILD_CPLUSPLUS_TOOLS):BUILD_CPLUSPLUS_TOOLS=$$(BUILD_CPLUSPLUS_TOOLS)
!isEmpty(BUILD_CPLUSPLUS_TOOLS): SUBDIRS += cplusplus-keywordgen