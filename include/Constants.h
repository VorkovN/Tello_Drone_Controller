#pragma once

namespace constants
{
const char *const TELLO_SERVER_IP{"192.168.10.1"};// sudo arp-scan --interface=wlp1s0 --localnet
const char *const TELLO_SERVER_COMMAND_PORT = "8889";
const int LOCAL_CLIENT_COMMAND_PORT = 9000;
const int LOCAL_SERVER_STATE_PORT = 8890;
const int VIDEO_FRAME_DELAY = 5 ;
const int STATUS_DELAY = 100   ;
}