use std::fs::read_to_string;

fn parse_number_from_line(line: &str) -> u64 {
    line.split_once(' ').unwrap().1
        .split(' ').filter(|line| {
            !line.is_empty()
        }).collect::<String>().parse::<u64>().unwrap()
}

fn count_winning_strategies(time: u64, distance: u64) -> u64 {
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

    let time = parse_number_from_line(&lines[0]);
    let distance = parse_number_from_line(&lines[1]);
    
    println!("time: {:?}", time);
    println!("distance: {:?}", distance);

    println!("Winning strategies: {}", count_winning_strategies(time, distance));
}