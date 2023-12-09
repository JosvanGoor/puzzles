use std::{fs::read_to_string, collections::HashMap};

fn parse_input() -> (String, HashMap<String, (String, String)>) {
    let lines = read_to_string("input.txt").unwrap().lines().map(|line| {
        String::from(line)
    }).collect::<Vec<_>>();

    let instr = lines[0].trim();
    let mut mapping: HashMap<String, (String, String)> = HashMap::new();

    for line in &lines[2..] {
        let (key, instructions) = line.split_once('=').unwrap();
        let (left, right) = instructions.trim().split_once(' ').unwrap();
        mapping.insert(String::from(key.trim()), (String::from(&left[1..4]), String::from(&right[..3])));
    }

    (String::from(instr), mapping)
}

fn main() {
    let (instructions, mapping) = parse_input();
    
    let mut position = String::from("AAA");
    let mut steps = 0;
    let mut caret = 0;

    loop {
        if position == "ZZZ" {
            break;
        }

        position = if instructions.as_bytes()[caret] == b'L' { mapping[&position].0.clone() } else {mapping[&position].1.clone() };
        caret = if caret + 1 == instructions.len() { 0 } else { caret +  1 };
        steps += 1;
    }

    println!("Number of steps taken: {}", steps);

}