def main():
    n = int(input())

    distance = []

    for i in range(n):
        line = list(map(int, input().split()))
        distance.append(line)

    dp = [[1e9 for i in range(n)] for mask in range(1 << n)]
    dp[0][0] = 0

    for mask in range(1 << n):
        for i in range(n):
            if dp[mask][i] == 1e9:
                continue

            for j in range(n):
                if not mask & (1 << j):
                    ans1 = dp[mask ^ (1 << j)][j]
                    ans2 = dp[mask][i] + distance[i][j]
                    ans = min(ans1, ans2)
                    dp[mask ^ (1 << j)][j] = ans

    print(dp[-1][0])


main()

