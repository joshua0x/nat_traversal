#  简单的锥形NAT   UDP 打洞验证

##   NAT TYPE 
###   CONE NAT 
从同一个内部地址和端口出来的包，NAT关联规则中的外部源IP/PORT  保持不变.
分为3类 ：
1) 全锥形NAT（Full Cone NAT） 在一个新会话建立了公网/内网端口绑定之后，全锥形NAT接下来会接受对应公网端口的所有数据，无论是来自哪个IP。
2) 受限锥形NAT（Restricted Cone NAT） 只会转发符合某个条件的输入数据包。条件为：外部（源）IP地址匹配内网主机之前发送一个或多个数据包的结点的IP地址。 
3) 端口受限锥形NAT（Port-Restricted Cone NAT） 端口受限锥形NAT也类似，只当外部数据包的IP地址和端口号都匹配内网主机发送过的地址和端口号时才进行转发。 端口受限锥形NAT为内部结点提供了和对称NAT相同等级的保护，以隔离未关联的数据。



###  Symmetric Nat 
从同一个内部地址和端口出来，是 到另一个外部目标地址和端口，则NAT将使用不同的映射，转换成不同的端口. 同时 NAT设备在收到外部报文时，还需要按照端口受限CONE NAT 相同规则来决定是否转发到内部机器 。 

###  NAT  类型检测 
参考STUN 协议 （RFC3489），完成测试需要2个公网IP 用来检测是否是对称NAT。可以自己搭建，也有一些公开的STUN SERVER，例如stun.ideasip.com。

##  代码流程
###  编译 
make 

###  运行
仅在CONE NAT 下才能打洞采成功。
udp_punch.c 为转发服务端代码
peer1.c peer2.c  运行在NAT 后。
在服务器、NAT后的机器 上防火墙打开 对应的UDP PORT。



## 参考
[0]https://www.ietf.org/rfc/rfc3489.txt
[1]https://github.com/pannzh/P2P-Over-MiddleBoxes-Demo
[2]https://gist.github.com/koenbollen/464613
[3]https://www.zhihu.com/question/20436734




