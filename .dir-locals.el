((c++-ts-mode
  (c-ts-mode-indent-offset . 4)
  (tab-width . 4)
  (indent-tabs-mode . nil)
  (compile-command . "cmake --build build -j$(nproc)")
  (gud-gdb-history . nil)
  (gud-gdb-command-name . "gdb -q -i=mi --args ./build/LearnOpenGL")))
