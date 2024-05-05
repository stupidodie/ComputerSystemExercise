int sum(int *nums, int n) {
  int t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = 0, t6 = 0, t7 = 0, t8 = 0;
  for (int i = 0; i < n; i += 8) {
    t1 += nums[i];
    t2 += nums[i + 1];
    t3 += nums[i + 2];
    t4 += nums[i + 3];
    t5 += nums[i + 4];
    t6 += nums[i + 5];
    t7 += nums[i + 6];
    t8 += nums[i + 7];
  }

  return t1 + t2 + t3 + t4 + t5 + t6 + t7 + t8;
}
