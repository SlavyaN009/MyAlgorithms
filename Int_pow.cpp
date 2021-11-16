uint64_t ipow(uint64_t base, int e, int m)
{
    uint64_t result = 1;
    for (;;)
    {
        if (e & 1)
            result = (result * base) % m;
        e >>= 1;
        if (!e)
            break;
        base = (base * base) % m;
    }

    return result;
}
