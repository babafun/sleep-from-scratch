This is a completely standalone sleep implementation for x86_64 Linux that depends only on the Linux kernel.

I made it for my YouTube video which you can find here:

https://www.youtube.com/watch?v=IbibjkI1kIs

Sources:

[GCC inline assembly howto](https://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html#toc6)

[System V Application Binary Interface](https://raw.githubusercontent.com/wiki/hjl-tools/x86-psABI/x86-64-psABI-1.0.pdf)

[GCC Manual](https://gcc.gnu.org/onlinedocs/gcc/Machine-Constraints.html)


License: either MIT or Public Domain, whichever you prefer.


Build:

```
rustc -o sleep_rs ./sleep.rs --edition=2024 -Copt-level=3 -Clink-arg=-nostartfiles  -Cpanic=abort -Cstrip=debuginfo

gcc -o sleep_c -O3 -nolibc -fno-stack-protector -nostartfiles sleep.c
```