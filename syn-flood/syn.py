import struct

PER_FILE_HEADER_SIZE = 24
PER_PACKET_HEADER_SIZE = 16


with open("./synflood.pcap", "rb") as f:
    magic_number, major, minor, _, _, _, llh_type = struct.unpack(
        "<IHHIIII", f.read(PER_FILE_HEADER_SIZE)
    )
    assert magic_number == 0xA1B2C3D4
    assert llh_type == 0
    print(f"Read pcap protocal version major {major} minor {minor}")
    counter = 0
    initial = 0
    asked = 0
    while True:
        # parsing each packet
        per_packet = f.read(PER_PACKET_HEADER_SIZE)
        if len(per_packet) == 0:
            break
        counter = counter + 1
        _, _, packet_length, un_truncated_length = struct.unpack("<IIII", per_packet)
        assert packet_length == un_truncated_length
        packet = f.read(packet_length)
        # Firstly ipv4 then tcp
        assert struct.unpack("<I", packet[0:4])[0] == 2  # ipv4
        assert (packet[4] & 0xF0) >> 4 == 4  # ipv4 version
        assert (packet[4] & 0xF) << 2 == 20  # ihl size
        assert packet[13] == 6  # tcp protocol
        src, dst, _, _, flags = struct.unpack("!HHIIH", packet[24:38])
        ack = (flags & 0x10) > 0
        syn = (flags & 0x2) > 0
        if dst == 80 and syn:
            initial += 1
        if src == 80 and ack:
            ack += 1
        print(f"{src} -> {dst} {syn and " SYN" or ""} {ack and " ACK" or ""}")
    print(f"{counter} packets parsed {initial} connections, {asked} asked ")
