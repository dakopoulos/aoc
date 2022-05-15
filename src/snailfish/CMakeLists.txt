add_library(snailfish
    num.cpp
    read.cpp
    add.cpp
)

# executable for testing reduction
add_executable(test-add
    test-add.cpp
)
target_link_libraries(test-add
    snailfish
)

# executable for testing magnitude
add_executable(test-magn
    test-magn.cpp
)
target_link_libraries(test-magn
    snailfish
)
