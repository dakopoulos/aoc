add_library(reactor
    geom.cpp
    reactor.cpp
    read.cpp
)

# executable for testing reduction (on-the-fly)
add_executable(init-and-reboot
    init-and-reboot.cpp
)
target_link_libraries(init-and-reboot
    reactor
)
