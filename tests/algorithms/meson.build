# Test compilation rules:


# tests = ['gunit_driver.cpp']
# gunit_executable = executable('fastnet_test_gunit',
#                         tests,
#                         include_directories : inc)
# #                        dependencies : structures)

# GUnit deterministic tests:
# test('Structures gtest 1', 'test')

tests_src = [
  'mincut.cpp',
]  
gtest_algorithms = executable(
  'gtest_algorithms',
  tests_src,
  include_directories : inc,
  dependencies : [
    gtest_dep,
    gmock_dep],
)    
test('gtest tests/algorithm', gtest_algorithms)