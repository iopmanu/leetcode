    string maxSumOfSquares(int num, int sum) {
        if (sum > 9 * num) {
            return "";
        }

        int remainder = sum % 9;
        std::string result(sum / 9, '9');
        if (remainder > 0) {
            result.push_back('0' + remainder);
        }

        result.append(num - result.size(), '0');
        return result;
    }
