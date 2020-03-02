# Test compilation rules:


# tests = ['gunit_driver.cpp']
# gunit_executable = executable('fastnet_test_gunit',
#                         tests,
#                         include_directories : inc)
# #                        dependencies : structures)

# GUnit deterministic tests:
# test('Structures gtest 1', 'test')

tests_src = [
  'hello_test.cpp',
  'graph_base_tests.cpp'
]  
gtest_structures = executable(
  'gtest_structures',
  tests_src,
  include_directories : inc,
  dependencies : [
    gtest_dep,
    gmock_dep],
)    
test('gtest tests/succint', gtest_structures)