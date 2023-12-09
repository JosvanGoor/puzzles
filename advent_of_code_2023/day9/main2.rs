use std::fs::read_to_string;

fn extrapolate_backwards(sequence: &Vec<i64>) -> i64 {
    if sequence.iter().all(|num| { *num == 0 }) {
        return 0;
    }

    let mut deltas: Vec<i64> = Vec::new();
    for idx in 1..sequence.len() {
        deltas.push(sequence[idx - 1] - sequence[idx]);
    }

    sequence.first().unwrap() + extrapolate_backwards(&deltas)
}

fn main() {
    let sequences = read_to_string("input.txt").unwrap().lines().map(|line| {
        line.split(' ').map(|num| {
            num.parse::<i64>().unwrap()
        }).collect::<Vec<_>>()
    }).collect::<Vec<_>>();

    println!("Sum of extrapolations: {}", sequences.iter().map(|sequence| {
        extrapolate_backwards(sequence)
    }).sum::<i64>());
}