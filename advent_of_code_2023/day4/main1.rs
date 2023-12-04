use std::fs::read_to_string;
use std::collections::HashSet;

fn main() {
    let mut score = 0;

    for line in read_to_string("input.txt").unwrap().lines() {
        let (_, card) = line.split_once(':').unwrap();
        let (numbers, winners) = card.split_once('|').unwrap();
        
        let numbers = numbers.split(' ').filter(|numstr| { !numstr.is_empty() }).map(|number| {
            number.parse::<i32>().unwrap()
        }).collect::<Vec<_>>();

        let winners = winners.split(' ').filter(|numstr| { !numstr.is_empty() }).map(|number| {
            number.parse::<i32>().unwrap()
        }).collect::<HashSet<_>>();

        let mut card_score = 0;
        for number in numbers {
            if winners.contains(&number) {
                card_score = if card_score == 0 { 1 } else { card_score * 2 };
            }
        }
        
        score += card_score;
    }

    println!("score: {}", score);
}