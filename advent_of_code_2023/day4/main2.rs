use std::cmp::min;
use std::fs::read_to_string;
use std::collections::HashSet;

struct Card {
    numbers: Vec<i32>,
    winners: HashSet<i32>
}

fn count_wins(card: &Card) -> usize {
    let mut hits = 0;

    for number in &card.numbers {
        if card.winners.contains(&number) {
            hits += 1;
        }
    }

    hits
}

fn main() {
    let cards = read_to_string("input.txt").unwrap().lines().map(|line| {
        let (_, card) = line.split_once(':').unwrap();
        let (numbers, winners) = card.split_once('|').unwrap();
        
        let numbers = numbers.split(' ').filter(|numstr| { !numstr.is_empty() }).map(|number| {
            number.parse::<i32>().unwrap()
        }).collect::<Vec<_>>();

        let winners = winners.split(' ').filter(|numstr| { !numstr.is_empty() }).map(|number| {
            number.parse::<i32>().unwrap()
        }).collect::<HashSet<_>>();

        Card{numbers: numbers, winners: winners}
    }).collect::<Vec<_>>();

    let mut stacks = vec![1; cards.len()];

    for idx in 0..stacks.len() {
        let score = count_wins(&cards[idx]);

        for wins in (idx + 1)..min(idx + score + 1, stacks.len()) {
            stacks[wins] += stacks[idx];
        }
    }

    println!("Total #cards: {}", stacks.iter().sum::<i32>());
}