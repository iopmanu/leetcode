                    if (arr[i] != arr[j] && arr[j] != arr[k] && arr[i] != arr[k]) {
                        result = (result + 1LL * counts[arr[i]] * counts[arr[j]] * counts[arr[k]]) % MOD;
                    } else if (arr[i] == arr[j] && arr[i] != arr[k]) {
                        result = (result + 1LL * counts[arr[i]] * (counts[arr[i]] - 1) * counts[arr[k]] / 2) % MOD;
                    } else if (arr[j] == arr[k] && arr[i] != arr[j]) {
                        result = (result + 1LL * counts[arr[j]] * (counts[arr[j]] - 1) * counts[arr[i]] / 2) % MOD;
                    } else {
                        result = (result + 1LL * counts[arr[i]] * (counts[arr[i]] - 1) * (counts[arr[i]] - 2) / 6) % MOD;
                    }