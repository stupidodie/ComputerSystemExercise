fn encode(mut number: u64) -> Vec<u8> {
    let mut bytes: Vec<u8> = Vec::new();
    while number > 0 {
        let res: u8 = (0x7F & number).try_into().unwrap();
        number = number >> 7;
        if number == 0 {
            bytes.push(res);
        } else {
            bytes.push(res + 0x80);
        }
    }
    return bytes;
}

fn decode(bytes: Vec<u8>) -> u64 {
    let mut result: u64 = 0;
    let mut shift: usize = 0;
    for byte in bytes.iter() {
        result += ((*byte) as u64 & 0x7F) << shift;
        shift = shift + 7;
    }
    return result;
}
fn main() {
    assert_eq!(encode(150), vec![0x96, 0x1]);
    assert_eq!(decode(vec![0x96, 0x1]), 150);
    for number in 1..1 << 30 {
        assert_eq!(decode(encode(number)), number);
    }
}
