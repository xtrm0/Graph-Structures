# Test compilation rules:


# tests = ['gunit_driver.cpp']
# gunit_executable = executable('fastnet_test_gunit',
#                         tests,
#                         include_directories : inc)
# #                        dependencies : structures)

# GUnit deterministic tests:
# test('Structures gtest 1', 'test')

tests_src = files(
  'graph_base_tests.cpp',
)
project_test_sources += tests_src
gtest_structures = executable(
  'gtest_structures',
  tests_src,
  include_directories : inc,
  dependencies : [
    gtest_dep,
    gmock_dep],
)    
test('gtest tests/structures', gtest_structures, timeout: 1)