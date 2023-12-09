use std::{fs::read_to_string, collections::HashMap};

struct Route {
    offset: usize,
    loop_length: usize,
    current: usize
}

// copied from https://www.hackertouch.com/least-common-multiple-in-rust.html
fn lcm(first: usize, second: usize) -> usize {
    first * second / gcd(first, second)
}

fn gcd(first: usize, second: usize) -> usize {
    let mut max = first;
    let mut min = second;
    if min > max {
        let val = max;
        max = min;
        min = val;
    }

    loop {
        let res = max % min;
        if res == 0 {
            return min;
        }

        max = min;
        min = res;
    }
}					

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

fn find_route(start: String, instructions: &String, mapping: &HashMap<String, (String, String)>) -> usize {
    let mut caret = 0;
    let mut step = 0;
    let mut position = start.clone();
    loop {
        position = if instructions.as_bytes()[caret] == b'L' { mapping[&position].0.clone() } else { mapping[&position].1.clone() };
        step += 1;
        caret = if caret + 1 == instructions.len() { 0 } else { caret +  1 };
        
        if position.ends_with('Z') {
            return step;
        }
    }
}

fn main() {
    let (instructions, mapping) = parse_input();
    
    let positions = mapping.keys().filter(|key| {
        key.ends_with('A')
    }).map(|string| String::from(string)).collect::<Vec<_>>();

    println!("{:?}", positions);

    let routes = positions.iter().map(|start| {
        find_route(start.clone(), &instructions, &mapping)
    }).collect::<Vec<_>>();

    let mut steps = 1;
    for route in routes {
        steps = lcm(steps, route);
    }

    println!("Number of steps taken: {}", steps);

}