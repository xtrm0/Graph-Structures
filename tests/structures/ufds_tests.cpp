#include "structures/baseutils/assertions.hpp"
#include "structures/graph/adjacency_list.hpp"
#include "structures/graph/adjacency_matrix.hpp"
#include "structures/graph/compressed_sparse_rows.hpp"
#include "structures/graph/edge_list.hpp"
#include "structures/succinct/ufds.hpp"

#include <gtest/gtest.h>

#ifndef GTEST_HAS_TYPED_TEST
ERROR("NO typed tests")
#endif

using testing::Types;
#define TEST_HEADER() using DSType = typename TestFixture::DSType;

template <class T>
struct UFDS_Base_Test : public testing::Test {
  typedef T DSType;

 protected:
  UFDS_Base_Test() {}
};
using UFDSImplementations = ::testing::Types<DisjointSet>;

TYPED_TEST_SUITE(UFDS_Base_Test, UFDSImplementations);

TYPED_TEST(UFDS_Base_Test, EmptyConstructor) {
  TEST_HEADER();
  DSType ds;
  ASSERT_EQ(ds.N, 0);
}

TYPED_TEST(UFDS_Base_Test, Constructor) {
  TEST_HEADER();

  DSType ds = DSType(5);
  for (int i = 0; i < 5; i++) {
    ASSERT_EQ(ds.Find(i), i);
  }
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      ASSERT_EQ(ds.AreConnected(i, j), (i == j));
    }
  }
}

TYPED_TEST(UFDS_Base_Test, Union1) {
  TEST_HEADER();

  DSType ds = DSType(5);
  ds.Union(0, 1);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      bool shouldBeEqual = i == j;
      shouldBeEqual = shouldBeEqual || (i == 0 && j == 1);
      shouldBeEqual = shouldBeEqual || (i == 1 && j == 0);
      ASSERT_EQ(ds.AreConnected(i, j), shouldBeEqual);
    }
  }

  ds.Union(2, 3);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      bool shouldBeEqual = i == j;
      shouldBeEqual = shouldBeEqual || (i == 0 && j == 1);
      shouldBeEqual = shouldBeEqual || (i == 1 && j == 0);
      shouldBeEqual = shouldBeEqual || (i == 2 && j == 3);
      shouldBeEqual = shouldBeEqual || (i == 3 && j == 2);
      ASSERT_EQ(ds.AreConnected(i, j), shouldBeEqual);
    }
  }

  ds.Union(2, 4);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      bool shouldBeEqual = i == j;
      shouldBeEqual = shouldBeEqual || (i == 0 && j == 1);
      shouldBeEqual = shouldBeEqual || (i == 1 && j == 0);
      shouldBeEqual = shouldBeEqual || (i == 2 && (j == 3 || j == 4));
      shouldBeEqual = shouldBeEqual || (i == 3 && (j == 2 || j == 4));
      shouldBeEqual = shouldBeEqual || (i == 4 && (j == 2 || j == 3));
      ASSERT_EQ(ds.AreConnected(i, j), shouldBeEqual);
    }
  }

  ds.Union(2, 3);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      bool shouldBeEqual = i == j;
      shouldBeEqual = shouldBeEqual || (i == 0 && j == 1);
      shouldBeEqual = shouldBeEqual || (i == 1 && j == 0);
      shouldBeEqual = shouldBeEqual || (i == 2 && (j == 3 || j == 4));
      shouldBeEqual = shouldBeEqual || (i == 3 && (j == 2 || j == 4));
      shouldBeEqual = shouldBeEqual || (i == 4 && (j == 2 || j == 3));
      ASSERT_EQ(ds.AreConnected(i, j), shouldBeEqual);
    }
  }

  ds.Union(3, 1);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      ASSERT(ds.AreConnected(i, j));
    }
  }
}

TYPED_TEST(UFDS_Base_Test, Random1) {
  TEST_HEADER();

  const int SET_SIZE = 1000;
  auto REF_TRANSFORM = [](int x) { return SET_SIZE - x; };
  DSType ds = DSType(SET_SIZE);
  DisjointSet reference = DSType(SET_SIZE * 2);

  for (int i = 0; i < SET_SIZE; i++) {
    reference.Union(i, SET_SIZE + i);
  }

  for (int i = 0; i < SET_SIZE * 100; i++) {
    int a, b, c, d;
    a = random() % SET_SIZE;
    b = random() % SET_SIZE;
    c = random() % 2;
    switch (c) {
      case 0:
        ASSERT_EQ(ds.AreConnected(a, b),
                  reference.AreConnected(REF_TRANSFORM(a), REF_TRANSFORM(b)));
        break;
      case 1:
        d = random() % 2;

        ds.Union(a, b);
        if (d == 0) {
          reference.Union(REF_TRANSFORM(a), REF_TRANSFORM(b));
        } else if (d == 1) {
          reference.Union(REF_TRANSFORM(a) + SET_SIZE,
                          REF_TRANSFORM(b) + SET_SIZE);
        }
        break;
      default:
        assert(false);
    }
  }
}