#include <cstdio>
#include <cstdlib>
#include <stdint.h>
#include "lightweightserial.h"
#include "ros/ros.h"
#include "slow_bldc/SetIntParam.h"

LightweightSerial *g_serial = NULL;

bool send_pkt(const uint8_t *pkt, const uint32_t len)
{
  if (len >= 256) {
    ROS_ERROR("refusing to send %d-byte packet. must be <256.",
        static_cast<int>(len));
    return false;
  }

  //ROS_INFO("sending %d-byte packet", static_cast<int>(len));
  uint8_t framed_pkt[len+5];
  framed_pkt[0] = 0xbe;
  framed_pkt[1] = 0xef;
  framed_pkt[2] = static_cast<uint8_t>(len);
  uint16_t csum = static_cast<uint16_t>(len);
  for (int i = 0; i < static_cast<int>(len); i++) {
    framed_pkt[i+3] = pkt[i];
    csum += pkt[i];  // so bad. do something smarter someday.
  }
  framed_pkt[len+3] = static_cast<uint8_t>(csum & 0xff);
  framed_pkt[len+4] = static_cast<uint8_t>(csum >> 8);
  return g_serial->write_block(framed_pkt, len+5);
}

bool set_led(bool on)
{
  uint8_t pkt[2] = { 0x01, 0x00 };
  if (on)
    pkt[1] = 1;
  return send_pkt(pkt, sizeof(pkt));
}

bool set_int_param(slow_bldc::SetIntParam::Request &request,
    slow_bldc::SetIntParam::Response &response)
{
  int param_name_len = static_cast<int>(request.param.name.size());
  if (param_name_len > 250) {
    ROS_ERROR("param name len is too long: %s", request.param.name.c_str());
    return false;
  }
  ROS_INFO("set_int_param(%s, %d)",
      request.param.name.c_str(), request.param.value);
  uint8_t pkt[256] = {0};
  pkt[0] = 2;  // packet type 2 = set float param
  memcpy(&pkt[1], &request.param.value, 4);
  strcpy((char *)&pkt[5], request.param.name.c_str());
  return send_pkt(pkt, 6 + param_name_len);

}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "slow_bldc");
  ros::NodeHandle nh, nh_private("~");
  g_serial = new LightweightSerial("/dev/ttyUSB0", 1000000);  // todo: param
  if (!g_serial) {
    ROS_FATAL("couldn't open serial device");
    return 1;
  }
  ros::ServiceServer int_param_srv =
      nh.advertiseService("set_int_param", set_int_param);
  ros::Rate loop_rate(1000);
  ROS_INFO("entering slow_bldc spin loop");
  while (ros::ok()) {
    loop_rate.sleep();
    ros::spinOnce();
  }
  return 0;
}
