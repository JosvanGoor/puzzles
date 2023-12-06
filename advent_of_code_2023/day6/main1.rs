use std::fs::read_to_string;

fn parse_numbers_from_line(line: &str) -> Vec<i32> {
    line.split_once(' ').unwrap().1
        .split(' ').filter(|line| {
            !line.is_empty()
        }).map(|line| {
            line.parse::<i32>().unwrap()
        }).collect::<Vec<_>>()
}

fn count_winning_strategies(time: i32, distance: i32) -> i32 {
    let mut winners = 0;
    
    for hold in 0..time {
        if (time - hold) * hold > distance {
            winners += 1
        }
    }

    winners
}

fn main() {

    let lines = read_to_string("input.txt").unwrap().lines().map(|line| {
        String::from(line)
    }).collect::<Vec<_>>();

    let times = parse_numbers_from_line(&lines[0]);
    let distances = parse_numbers_from_line(&lines[1]);
    
    println!("times: {:?}", times);
    println!("distances: {:?}", distances);

    let mut score  = 1;
    for idx in 0..times.len() {
        score *= count_winning_strategies(times[idx], distances[idx]);
    }

    println!("Score: {}", score);
}