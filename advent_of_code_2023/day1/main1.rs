use std::fs::read_to_string;

fn main() {
    let mut calibration = 0;

    for line in read_to_string("input.txt").unwrap().lines() {
        let mut first = 0;
        let mut last = 0;
        let mut set_first = false;

        for char in line.chars() {
            if char.is_ascii_digit() {
                if !set_first {
                    first = char as i32 - '0' as i32;
                    set_first = true;
                }
                last = char as i32 - '0' as i32;
            }
        }

        calibration += 10 * first + last;
    }

    println!("{}", calibration);
}
