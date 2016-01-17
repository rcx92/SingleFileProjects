#include <unordered_map>
#include <map>
#include <Windows.h>
#include <algorithm>
#define HASH_SIZE 1000000
#define TEST_CASE_NUMBER 2900000
#define TABLE_SIZE (HASH_SIZE * 3)

struct HashMap{
	int first[HASH_SIZE];
	int nxt[TABLE_SIZE];
	int k[TABLE_SIZE];
	int v[TABLE_SIZE];
	int tot;

	bool find(int key, int &value){
		int index = first[key % HASH_SIZE];
		while (index != -1){
			if (k[index] == key) {
				value = v[index];
				return true;
			}
			index = nxt[index];
		}
		return false;
	}

	void insert(int key, int value){
		int oriIndex = key % HASH_SIZE;
		int index = first[oriIndex];
		while (index != -1){
			if (k[index] == key) {
				value = v[index];
				return;
			}
			index = nxt[index];
		}
		nxt[tot] = first[oriIndex];
		first[oriIndex] = tot;
		k[tot] = key;
		v[tot] = value;
		++tot;
	}
	void init(){
		for (int i = 0; i < HASH_SIZE; ++i){
			first[i] = -1;
		}
	}
}custom_map;

std::unordered_map<int, int> std_map;
std::map<int, int> std_tree_map;

int test_case_key[TEST_CASE_NUMBER];
int test_case_value[TEST_CASE_NUMBER];
int random_query[TEST_CASE_NUMBER];
int answer1[TEST_CASE_NUMBER];
int answer2[TEST_CASE_NUMBER];
int rand_answer1[TEST_CASE_NUMBER];
int rand_answer2[TEST_CASE_NUMBER];


int random(){
	return (rand() << 16) + rand();
}

int main(){
	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	QueryPerformanceFrequency(&nFreq);
	custom_map.init();
	for (int i = 0; i < TEST_CASE_NUMBER; ++i) test_case_key[i] = random();
	for (int i = 0; i < TEST_CASE_NUMBER; ++i) test_case_value[i] = random();
	for (int i = 0; i < TEST_CASE_NUMBER; ++i) random_query[i] = random();
	for (int i = 0; i < TEST_CASE_NUMBER; ++i){
		answer1[i] = answer2[i] = rand_answer1[i] = rand_answer2[i] = -1;
	}
	QueryPerformanceCounter(&nBeginTime);
	for (int i = 0; i < TEST_CASE_NUMBER; ++i) std_map.emplace(test_case_key[i], test_case_value[i]);
	for (int i = 0; i < TEST_CASE_NUMBER; ++i) {
		auto it = std_map.find(test_case_key[i]);
		if (it != std_map.end()) answer1[i] = it->second;
	}
	/*for (int i = 0; i < TEST_CASE_NUMBER; ++i) {
		auto it = std_map.find(random_query[i]);
		if (it != std_map.end()) rand_answer1[i] = it->second;
	}*/
	QueryPerformanceCounter(&nEndTime);
	printf("stdtime=%.10f\n", (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / nFreq.QuadPart);


	QueryPerformanceCounter(&nBeginTime);
	for (int i = 0; i < TEST_CASE_NUMBER; ++i) std_tree_map.emplace(test_case_key[i], test_case_value[i]);
	for (int i = 0; i < TEST_CASE_NUMBER; ++i) {
		auto it = std_tree_map.find(test_case_key[i]);
		if (it != std_tree_map.end()) answer1[i] = it->second;
	}
	/*for (int i = 0; i < TEST_CASE_NUMBER; ++i) {
	auto it = std_map.find(random_query[i]);
	if (it != std_map.end()) rand_answer1[i] = it->second;
	}*/
	QueryPerformanceCounter(&nEndTime);
	printf("std tree map time=%.10f\n", (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / nFreq.QuadPart);

	QueryPerformanceCounter(&nBeginTime);

	for (int i = 0; i < TEST_CASE_NUMBER; ++i) custom_map.insert(test_case_key[i], test_case_value[i]);
	for (int i = 0; i < TEST_CASE_NUMBER; ++i) {
		custom_map.find(test_case_key[i], answer2[i]);
	}
	//for (int i = 0; i < TEST_CASE_NUMBER; ++i) {
	//	custom_map.find(random_query[i], rand_answer2[i]);
	//}
	QueryPerformanceCounter(&nEndTime);
	printf("Mytime=%.10f\n", (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / nFreq.QuadPart);
	for (int i = 0; i < TEST_CASE_NUMBER; ++i){
		if (answer1[i] != answer2[i]){
			printf("Testcase %d wrong!\n", i);
		}
	}
	for (int i = 0; i < TEST_CASE_NUMBER; ++i){
		if (rand_answer1[i] != rand_answer2[i]){
			printf("Random query %d wrong!\n", i);
		}
	}
	int sum;

	QueryPerformanceCounter(&nBeginTime);
	sum = 0;
	for (auto it = std_map.begin(); it != std_map.end(); ++it){
		sum += it->first;
	}
	QueryPerformanceCounter(&nEndTime);

	printf("std map time=%.10f sum = %d\n", (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / nFreq.QuadPart, sum);


	QueryPerformanceCounter(&nBeginTime);
	sum = 0;
	for (auto it = std_tree_map.begin(); it != std_tree_map.end(); ++it){
		sum += it->first;
	}
	QueryPerformanceCounter(&nEndTime);

	printf("std tree map time=%.10f sum = %d\n", (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / nFreq.QuadPart, sum);

	std::vector<int> v;
	for (int i = 0; i < TEST_CASE_NUMBER; ++i) v.push_back(test_case_key[i]);
	std::sort(v.begin(), v.end());
	v.erase(std::unique(v.begin(), v.end()), v.end());
	QueryPerformanceCounter(&nBeginTime);
	sum = 0;
	for (auto it = v.begin(); it != v.end(); ++it){
		sum += *it;
	}
	QueryPerformanceCounter(&nEndTime);
	printf("vectortime=%.10f sum = %d\n", (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / nFreq.QuadPart, sum);

	QueryPerformanceCounter(&nBeginTime);
	sum = 0;
	for (int i = 0; i < TEST_CASE_NUMBER; ++i){
		sum += test_case_key[i];
	}
	QueryPerformanceCounter(&nEndTime);
	printf("arraytime++=%.10f sum = %d\n", (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / nFreq.QuadPart, sum);


	QueryPerformanceCounter(&nBeginTime);
	sum = 0;
	for (int i = 0; i < HASH_SIZE; ++i){
		int k = custom_map.first[i];
		while (k != -1){
			sum += custom_map.k[k];
			k = custom_map.nxt[k];
		}
	}
	QueryPerformanceCounter(&nEndTime);
	printf("Custom Map time=%.10f sum = %d\n", (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / nFreq.QuadPart, sum);



	getchar();
	return 0;
}