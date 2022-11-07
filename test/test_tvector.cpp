#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);
  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	double arr[] = { 10.0, -2.0, 3.0, 4.0 };
	size_t size = 4;
	TDynamicVector<double> v(arr, size);
	TDynamicVector<double> copy(v);
	EXPECT_TRUE(v == copy);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	double arr[] = { 10.0, -2.0, 3.0, 4.0 };
	size_t size = 4;
	TDynamicVector<double> v(arr, size);
	TDynamicVector<double> copy(v);
	EXPECT_TRUE(&v[0] != &copy[0]);
}

TEST(TDynamicVector, can_get_size)
{
	TDynamicVector<int> v(4);
	EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
	TDynamicVector<int> v(4);
	v[0] = 4;
	EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v.at(-1));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v.at(4));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(4);
	ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> a(4);
	TDynamicVector<int> b(4);
	a = b;
	EXPECT_EQ(a, b);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> a(1);
	TDynamicVector<int> b(4);
	a = b;
	EXPECT_EQ(4, a.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> a(40);
	TDynamicVector<int> b(4);
	a = b;
	EXPECT_EQ(a, b);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	int arr[] = { 10, -1, 2, 0 };
	TDynamicVector<int> v1(arr, 4), v2(arr, 4);
	EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> a(4);
	EXPECT_EQ(1, a == a);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> a(4);
	TDynamicVector<int> b(40);
	EXPECT_EQ(0, a == b);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v(3), res(3);
	v[0] = 2;
	v[1] = -1;
	v[2] = 0;
	v = v + 2;
	res[0] = 4;
	res[1] = 1;
	res[2] = 2;
	EXPECT_EQ(res, v);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v(3), res(3);
	v[0] = 2;
	v[1] = -1;
	v[2] = 0;
	v = v - 2;
	res[0] = 0;
	res[1] = -3;
	res[2] = -2;
	EXPECT_EQ(res, v);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v(3), res(3);
	v[0] = 2;
	v[1] = -1;
	v[2] = 0;
	v = v * 2;
	res[0] = 4;
	res[1] = -2;
	res[2] = 0;
	EXPECT_EQ(res, v);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v1(2), v2(2), res(2);
	v1[0] = 1;
	v1[1] = 2;
	v2[0] = 3; 
	v2[1] = 4;
	res[0] = 4;
	res[1] = 6;
	EXPECT_EQ(res, v1 + v2);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> a(4);
	TDynamicVector<int> b(40);
	ASSERT_ANY_THROW(a + b);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v1(2), v2(2), res(2);
	v1[0] = 1;
	v1[1] = 2;
	v2[0] = 3;
	v2[1] = 4;
	res[0] = -2;
	res[1] = -2;
	EXPECT_EQ(res, v1 - v2);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> a(4);
	TDynamicVector<int> b(40);
	ASSERT_ANY_THROW(a - b);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v1(2), v2(2);
	v1[0] = 1;
	v1[1] = 2;
	v2[0] = 3;
	v2[1] = 4;
	int res = 11;
	EXPECT_EQ(res, v1 * v2);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> a(4);
	TDynamicVector<int> b(40);
	ASSERT_ANY_THROW(a * b);
}



