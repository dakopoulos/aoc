add_library(reactor
    geom.cpp
    reactor.cpp
    read.cpp
)

# executable for testing reduction
add_executable(load-and-reboot
    load-and-reboot.cpp
)
target_link_libraries(load-and-reboot
    reactor
)

# executable for testing reduction (on-the-fly)
add_executable(reboot-on-the-fly
    reboot-on-the-fly.cpp
)
target_link_libraries(reboot-on-the-fly
    reactor
)
