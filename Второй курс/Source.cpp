//SHELL

int findStepsKnut(int nowLen)
{
    int size = 0;
    int k = 1;
    while (nowLen > k)
    {
        k = 3 * k + 1;
        size++;
    }
    return size;
}

int* InitializeGapKnut(int steps)
{
    int* h = new int[steps];

    h[steps - 1] = 1;
    for (int t = steps - 2; t >= 0; t--)
    {
        h[t] = 3 * h[t + 1] + 1;
    }

    return h;
}

void Shell(int* mass, int len)
{
    int stepsAmount;
    int* steps;

    stepsAmount = findStepsKnut(len);
    steps = InitializeGapKnut(stepsAmount);

    int i = 0, h, b, j, x, k;
    while (i < stepsAmount)
    {
        h = steps[i];
        b = 0;
        while (b < h)
        {
            j = b + h;
            while (j < len)
            {
                x = mass[j];
                k = j - h;

                while (k >= 0 && mass[k] > x)
                {
                    mass[k + h] = mass[k];
                    k -= h;
                }

                mass[k + h] = x;
                j += h;
            }


            b++;
        }
        i++;
    }
    delete[] steps;
}




void makeHeap(int* mass, int n, int i) {
    int largest = i;
    if (2 * i + 1 < n and mass[2 * i + 1] > mass[largest]) largest = 2 * i + 1;
    if (2 * i + 2 < n and mass[2 * i + 2] > mass[largest]) largest = 2 * i + 2;

    if (largest != i)
    {
        //swap(mass[i], mass[largest]);               //!!!
        makeHeap(mass, n, largest);
    }

}

void PyramidSort(int* mass, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        makeHeap(mass, n, i);

    for (int i = n - 1; i >= 0; i--)
    {
        //swap(mass[0], mass[i]);                    //!!!
        makeHeap(mass, i, 0);
    }
}
