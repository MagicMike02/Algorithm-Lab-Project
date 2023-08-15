#include "../../Resources/C/Unity/unity.h"
#include "skiplist.h"


static void testSkipListEmpty(){

  SkipList* skl = newSkipList(compareField1); // Skip list created -> list is empty

  //testing if list is actually empty (item =NULL, maxlevel = MAX_HEIGHT ...)
  TEST_ASSERT_EQUAL(NULL, skl->head->item);
  TEST_ASSERT_EQUAL(0, skl->max_level);
  TEST_ASSERT_EQUAL(MAX_HEIGHT, skl->head->size);

  TEST_ASSERT_TRUE(skl->head->next[1] == NULL);

  deleteSkipList(skl);

}

static void testSkipListOneElement(){
  void* result;
  SkipList* skl = newSkipList(compareField1); // Skip list created -> list is empty

  insertSkipList(skl, "a");
  //SkipList_print(skl);

  result = searchSkipList(skl, "a");

  TEST_ASSERT_NOT_NULL(result);
  TEST_ASSERT_TRUE(skl->head->next[1]->next[1] == NULL);

  deleteSkipList(skl);
}

static void testSkipListNElements(){
  void* result;
  SkipList* skl = newSkipList(compareField1); // Skip list created -> list is empty

  insertSkipList(skl, "a");
  insertSkipList(skl, "b");
  insertSkipList(skl, "c");
  SkipList_print(skl);

  result = searchSkipList(skl, "a");
  TEST_ASSERT_NOT_NULL(result);

  result = searchSkipList(skl, "a");
  TEST_ASSERT_NOT_NULL(result);

  deleteSkipList(skl);
}

static void testSkipListNEqualElements(){
  void* result;
  SkipList* skl = newSkipList(compareField1); // Skip list created -> list is empty

  insertSkipList(skl, "a");
  insertSkipList(skl, "a");
  insertSkipList(skl, "a");
  //SkipList_print(skl);

  result = searchSkipList(skl, "a");
  TEST_ASSERT_NOT_NULL(result);

  result = searchSkipList(skl, "a");
  TEST_ASSERT_NOT_NULL(result);

  deleteSkipList(skl);
}

static void testSkipListNInteger(){
  void* result;
  SkipList* skl = newSkipList(compareField2);

  insertSkipList(skl, (void*)2);
  insertSkipList(skl, (void*)1);
  insertSkipList(skl, (void*)3);

  result = searchSkipList(skl, (void*)1); //not null since he DID founds the item
  TEST_ASSERT_NOT_NULL(result);

  result = searchSkipList(skl, (void*)7); // null since he DOES NOT found the item
  TEST_ASSERT_NULL(result);

  deleteSkipList(skl);
}

//MAIN TEST WITH UNITY C TESTs
int main(){
  UNITY_BEGIN();

  RUN_TEST(testSkipListEmpty);
  RUN_TEST(testSkipListOneElement);
  RUN_TEST(testSkipListNElements);
  RUN_TEST(testSkipListNEqualElements);
  RUN_TEST(testSkipListNInteger);

  UNITY_END();
}

