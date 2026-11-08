#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrixTriangle, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicMatrixTriangle<int> m(5));
}

TEST(TDynamicMatrixTriangle, cant_create_too_large_matrix)
{
	ASSERT_ANY_THROW(TDynamicMatrixTriangle<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrixTriangle, throws_when_create_matrix_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicMatrixTriangle<int> m(-5));
}

TEST(TDynamicMatrixTriangle, can_create_copied_matrix)
{
	TDynamicMatrixTriangle<int> m(5);

	ASSERT_NO_THROW(TDynamicMatrixTriangle<int> m1(m));
}

TEST(TDynamicMatrixTriangle, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrixTriangle<int> m1(4);
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = i; j < 4; j++) {
			m1[i][j] = 1;
		}
	}
	TDynamicMatrixTriangle<int> m2(m1);
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = i; j < 4; j++) {
			EXPECT_EQ(m1[i][j], m2[i][j]);
		}
	}
}

TEST(TDynamicMatrixTriangle, copied_matrix_has_its_own_memory)
{
	TDynamicMatrixTriangle<int> m1(4);
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = i; j < 4; j++) {
			m1[i][j] = 1;
		}
	}
	TDynamicMatrixTriangle<int> m2(m1);
	m1[0][0] = 2;
	EXPECT_EQ(1, m2[0][0]);
}

//TEST(TDynamicMatrixTriangle, can_get_size){ADD_FAILURE();}

TEST(TDynamicMatrixTriangle, can_set_and_get_element)
{
	TDynamicMatrixTriangle<int> m1(4);
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = i; j < 4; j++) {
			m1[i][j] = 1;
		}
	}
	m1[0][1] = 2;
	EXPECT_EQ(1, m1[0][0]);
	EXPECT_EQ(2, m1[0][1]);
}

TEST(TDynamicMatrixTriangle, throws_when_set_element_with_negative_index)
{
	TDynamicMatrixTriangle<int> m1(4);
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = i; j < 4; j++) {
			m1[i][j] = 1;
		}
	}
	ASSERT_ANY_THROW(m1[0][-1] = 4);
}

TEST(TDynamicMatrixTriangle, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrixTriangle<int> m1(4);
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = i; j < 4; j++) {
			m1[i][j] = 1;
		}
	}
	ASSERT_ANY_THROW(m1[0][15] = 4);
}

TEST(TDynamicMatrixTriangle, can_assign_matrix_to_itself)
{
	TDynamicMatrixTriangle<int> m1(4);
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = i; j < 4; j++) {
			m1[i][j] = 1;
		}
	}
	m1 = m1;
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = i; j < 4; j++) {
			EXPECT_EQ(1, m1[i][j]);
		}
	}
}

TEST(TDynamicMatrixTriangle, can_assign_matrices_of_equal_size)
{
	TDynamicMatrixTriangle<int> m1(4);
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = i; j < 4; j++) {
			m1[i][j] = 1;
		}
	}
	TDynamicMatrixTriangle<int> m2(4);
	m2 = m1;
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = i; j < 4; j++) {
			EXPECT_EQ(1, m2[i][j]);
		}
	}
}

TEST(TDynamicMatrixTriangle, assign_operator_change_matrix_size)
{
	TDynamicMatrixTriangle<int> m1(4);
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = i; j < 4; j++) {
			m1[i][j] = 1;
		}
	}
	TDynamicMatrixTriangle<int> m2(10);
	m2 = m1;
	EXPECT_EQ(4, m2.size());
}

TEST(TDynamicMatrixTriangle, can_assign_matrices_of_different_size)
{
	TDynamicMatrixTriangle<int> m1(4);
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = i; j < 4; j++) {
			m1[i][j] = 1;
		}
	}
	TDynamicMatrixTriangle<int> m2(10);
	m2 = m1;
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = i; j < 4; j++) {
			EXPECT_EQ(1, m2[i][j]);
		}
	}
	ASSERT_ANY_THROW(m2[0][4]);
}

TEST(TDynamicMatrixTriangle, compare_equal_matrices_return_true)
{
	TDynamicMatrixTriangle<int> m1(4);
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = i; j < 4; j++) {
			m1[i][j] = 1;
		}
	}
	TDynamicMatrixTriangle<int> m2(m1);
	EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrixTriangle, compare_matrix_with_itself_return_true)
{
	TDynamicMatrixTriangle<int> m1(4);
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = i; j < 4; j++) {
			m1[i][j] = 1;
		}
	}
	EXPECT_TRUE(m1 == m1);
}

TEST(TDynamicMatrixTriangle, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrixTriangle<int> m1(4);
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = i; j < 4; j++) {
			m1[i][j] = 1;
		}
	}
	TDynamicMatrixTriangle<int> m2(10);
	for (size_t i = 0; i < 10; i++) {
		for (size_t j = i; j < 10; j++) {
			m2[i][j] = 1;
		}
	}
	EXPECT_FALSE(m1 == m2);
}

TEST(TDynamicMatrixTriangle, can_add_matrices_with_equal_size)
{
	TDynamicMatrixTriangle<int> m1(10);
	for (size_t i = 0; i < 10; i++) {
		for (size_t j = i; j < 10; j++) {
			m1[i][j] = 1;
		}
	}
	TDynamicMatrixTriangle<int> m2(10);
	for (size_t i = 0; i < 10; i++) {
		for (size_t j = i; j < 10; j++) {
			m2[i][j] = 2;
		}
	}
	TDynamicMatrixTriangle<int> res(m1);
	for (size_t i = 0; i < 10; i++) {
		for (size_t j = i; j < 10; j++) {
			res[i][j] = m1[i][j] + m2[i][j];
		}
	}
	EXPECT_EQ(res, m1 + m2);
}

TEST(TDynamicMatrixTriangle, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrixTriangle<int> m1(10);
	for (size_t i = 0; i < 10; i++) {
		for (size_t j = i; j < 10; j++) {
			m1[i][j] = 1;
		}
	}
	TDynamicMatrixTriangle<int> m2(8);
	for (size_t i = 0; i < 8; i++) {
		for (size_t j = i; j < 8; j++) {
			m2[i][j] = 2;
		}
	}
	EXPECT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrixTriangle, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrixTriangle<int> m1(10);
	for (size_t i = 0; i < 10; i++) {
		for (size_t j = i; j < 10; j++) {
			m1[i][j] = 1;
		}
	}
	TDynamicMatrixTriangle<int> m2(10);
	for (size_t i = 0; i < 10; i++) {
		for (size_t j = i; j < 10; j++) {
			m2[i][j] = 2;
		}
	}
	TDynamicMatrixTriangle<int> res(m1);
	for (size_t i = 0; i < 10; i++) {
		for (size_t j = i; j < 10; j++) {
			res[i][j] = m1[i][j] - m2[i][j];
		}
	}
	EXPECT_EQ(res, m1 - m2);
}

TEST(TDynamicMatrixTriangle, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrixTriangle<int> m1(10);
	for (size_t i = 0; i < 10; i++) {
		for (size_t j = i; j < 10; j++) {
			m1[i][j] = 1;
		}
	}
	TDynamicMatrixTriangle<int> m2(8);
	for (size_t i = 0; i < 8; i++) {
		for (size_t j = i; j < 8; j++) {
			m2[i][j] = 2;
		}
	}
	EXPECT_ANY_THROW(m1 - m2);
}


