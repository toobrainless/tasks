def main():
    with open('input.txt', 'r', encoding='utf-8') as file:
        data = file.readlines()
        arr = list(map(int, data[1].split()))
        prefixes = [0]
        prefix = 0
        for i in range(1, len(arr) + 1):
            prefix += arr[i - 1]
            prefixes.append(prefix)

        queries = int(data[2])
        # print(prefixes)
        for i in range(queries):
            l, r = map(int, data[i + 3].split())
            print(prefixes[r + 1] - prefixes[l])


main()

