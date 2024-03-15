#include <iostream>
#include <algorithm>
#include <execution>
#include <vector>

int main()
{
    std::vector<int> v = { 2, 5, 7, 4, 3, 9, 1, 2 };

    std::sort(std::execution::par, v.begin(), v.end());

    for (auto i : v)
    {
        std::cout << i << " ";
    }
    std::cout << "\nRunning for each...\n";

    std::for_each(std::execution::par, v.begin(), v.end(), [](int i)
        {
            std::cout << i << " ";
        }
    );

    std::cout << "\nRunning reduce...\n";

    int sum = std::reduce(std::execution::par, v.begin(), v.end());
    std::cout << "Sum: " << sum << "\n";

    std::cout << "\nRunning transform reduce...\n";

    sum = std::transform_reduce(std::execution::par, v.begin(), v.end(), 0, std::plus<>(), [](int x) {return x * x; });

    std::cout << "Sum: " << sum << "\n";

}
