add_library(reactor
    geom.cpp
    reactor.cpp
    read.cpp
)

# executable for testing reduction
add_executable(reboot-reactor
    reboot.cpp
)
target_link_libraries(reboot-reactor
    reactor
)
