# Create a variable to hold the list of source and header files
#file(GLOB_RECURSE SOURCE_FILES "*.cpp")
#file(GLOB_RECURSE HEADER_FILES "*.h")
## Associate the source files with the target using target_sources
#target_sources(lambda PRIVATE ${SOURCE_FILES} ${HEADER_FILES})