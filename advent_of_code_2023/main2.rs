use std::fs::read_to_string;
use std::vec::Vec;

fn inline_compare(line: &str, caret: usize, word: &str) -> bool {
    for idx in 0..word.len() {
        if (caret + idx)  == line.len() {
            return false
        }

        if line.as_bytes()[caret + idx] != word.as_bytes()[idx] {
            return false
        }

        // 3rd case: line is long enough and characters match
    }

    true
}

fn parse_to_numbers(line: &str) -> Vec<i32> {
    let mut rval: Vec<i32> = Vec::new();
    
    /*
        one
        eight
        nine

        four
        five

        two
        three

        six
        seven
    */

    let slice = line.as_bytes();
    for idx in 0..line.len() {
        match slice[idx] {
            b'0'..=b'9' => rval.push(slice[idx] as i32 - '0' as i32),
            
            b'o' => {
                if inline_compare(line, idx, "one") {
                    rval.push(1);
                }
            }

            b'e' => {
                if inline_compare(line, idx, "eight") {
                    rval.push(8);
                }
            }

            b'n' => {
                if inline_compare(line, idx, "nine") {
                    rval.push(9);
                }
            }

            b'f' => {
                if inline_compare(line, idx, "four") {
                    rval.push(4);
                } else if inline_compare(line, idx, "five") {
                    rval.push(5);
                }
            }

            b't' => {
                if inline_compare(line, idx, "two") {
                    rval.push(2);
                } else if inline_compare(line, idx, "three") {
                    rval.push(3);
                }
            }

            b's' => {
                if inline_compare(line, idx, "six") {
                    rval.push(6);
                } else if inline_compare(line, idx, "seven") {
                    rval.push(7);
                }
            }
            _ => ()
        }
    }

    return rval;
}

fn main() {
    let mut calibration = 0;

    for line in read_to_string("input.txt").unwrap().lines() {
        let numbers = parse_to_numbers(line);
        println!{"{:?}", numbers}

        let first = match numbers.first() {
            Some(n) => n,
            None => continue
        };

        let last = match numbers.last() {
            Some(n) => n,
            None => continue
        };

        calibration += 10 * first + last;
    }

    println!("{}", calibration);
}
