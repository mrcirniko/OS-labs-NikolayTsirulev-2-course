#include <gtest/gtest.h>

#include "topology.hpp"
#include "socket.hpp"
#include <thread>

TEST(FifthSeventhLabTest, SocketTest) {
    zmq::context_t context;
    zmq::socket_t repSocket(context, ZMQ_REP);
    bind(repSocket, 3);  

    std::thread serverThread([&repSocket]() {
        std::string receivedMessage = receiveMessage(repSocket);
        EXPECT_EQ(receivedMessage, "TestMSG");

        sendMessage(repSocket, "ReplyMSG");
    });

    zmq::socket_t reqSocket(context, ZMQ_REQ);
    connect(reqSocket, 3);

    sendMessage(reqSocket, "TestMSG");

    std::string replyMessage = receiveMessage(reqSocket);
    EXPECT_EQ(replyMessage, "ReplyMSG");

    disconnect(reqSocket, 3);
    unbind(repSocket, 3);
    serverThread.join();
}

TEST(FifthSeventhLabTest, TopologyTest) {
    Topology topology;

    topology.insert(1, -1);
    topology.insert(2, 1);
    topology.insert(3, 2);

    EXPECT_EQ(topology.find(1), 0);
    EXPECT_EQ(topology.find(2), 0);
    EXPECT_EQ(topology.find(3), 0);

    EXPECT_EQ(topology.getFirstId(0), 1);

    topology.erase(2);

    EXPECT_EQ(topology.find(2), -1);
}


int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}