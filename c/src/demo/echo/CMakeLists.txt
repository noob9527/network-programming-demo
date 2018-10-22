add_executable(
        echo-server1
        ./echo1/echo-server1.c
        ./init-server.c
        ./init-server.h
        ./echo.c
        ./echo.h
)

add_executable(
        echo-client1
        ./echo1/echo-client1.c
)

target_link_libraries(echo-server1 share)
target_link_libraries(echo-client1 share)

add_executable(
        echo-server2
        ./echo2/echo-server2.c
        ./init-server.c
        ./init-server.h
        ./echo.c
        ./echo.h
)

add_executable(
        echo-client2
        ./echo2/echo-client2.c
)

target_link_libraries(echo-server2 share)
target_link_libraries(echo-client2 share)


add_executable(
        echo-server3
        ./echo3/echo-server3.c
        ./init-server.c
        ./init-server.h
        ./echo.c
        ./echo.h
)

target_link_libraries(echo-server3 share)

add_executable(
        echo-server4
        ./echo4/echo-server4.c
        ./init-server.c
        ./init-server.h
        ./echo.c
        ./echo.h
)

target_link_libraries(echo-server4 share)
target_link_libraries(echo-server4 pthread)

add_executable(
        echo-server5
        ./echo5/echo-server5.c
        ./init-server.c
        ./init-server.h
        ./echo.c
        ./echo.h
)

target_link_libraries(echo-server5 share)

add_executable(
        echo-server6
        ./echo6/echo-server6.c
        ./init-server.c
        ./init-server.h
        ./echo.c
        ./echo.h
)

target_link_libraries(echo-server6 share)
