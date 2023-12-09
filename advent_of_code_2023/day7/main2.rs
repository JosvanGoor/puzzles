use std::{fs::read_to_string, collections::{HashMap, btree_map::Values}};

#[derive(Debug, Copy, Clone)]
#[derive(PartialEq, PartialOrd, Eq, Ord)]
enum Rank {
    HighCard,
    OnePair,
    TwoPair,
    ThreeOfAKind,
    FullHouse,
    FourOfAKind,
    FiveOfAKind,
}

impl Rank {

    fn signature(&self) -> Vec<i32> {
        match self {
            Rank::HighCard => vec![1, 1, 1, 1, 1],
            Rank::OnePair => vec![2, 1, 1, 1],
            Rank::TwoPair => vec![2, 2, 1],
            Rank::ThreeOfAKind => vec![3, 1, 1],
            Rank::FullHouse => vec![3, 2],
            Rank::FourOfAKind => vec![4, 1],
            Rank::FiveOfAKind => vec![5]
        }
    }

    fn matches(&self, hand: &Vec<i32>) -> bool {
        let signature = self.signature();
        if hand.len() != signature.len() {
            return false;
        }
        signature.iter().zip(hand.iter()).filter(|&(lhs, rhs)| lhs == rhs).count() == signature.len()
    }

    fn mapping() -> HashMap<Vec<i32>, Rank> {
        HashMap::from([
            (Rank::HighCard{}.signature(), Rank::HighCard),
            (Rank::OnePair{}.signature(), Rank::OnePair),
            (Rank::TwoPair{}.signature(), Rank::TwoPair),
            (Rank::ThreeOfAKind{}.signature(), Rank::ThreeOfAKind),
            (Rank::FullHouse{}.signature(), Rank::FullHouse),
            (Rank::FourOfAKind{}.signature(), Rank::FourOfAKind),
            (Rank::FiveOfAKind{}.signature(), Rank::FiveOfAKind),
        ])
    }

    fn card_values() -> HashMap<u8, i32> {
        HashMap::from([
            (b'J', 0),
            (b'2', 1),
            (b'3', 2),
            (b'4', 3),
            (b'5', 4),
            (b'6', 5),
            (b'7', 6),
            (b'8', 7),
            (b'9', 8),
            (b'T', 9),
            (b'Q', 10),
            (b'K', 11),
            (b'A', 12),
        ])
    }

    fn parse(line: &str, mapping: &HashMap<Vec<i32>, Rank>, values: &HashMap<u8, i32>) -> (Rank, u64) {
        if line == "JJJJJ" {
            return (Rank::FiveOfAKind, 0);
        }
        
        let mut counts = HashMap::<u8, i32>::new();
        let mut tiebreaker: u64 = 0;
        let mut jokers = 0;

        for idx in 0..line.len() {
            if line.as_bytes()[idx] == b'J' {
                jokers += 1;
            } else {
                *counts.entry(line.as_bytes()[idx]).or_insert(0) += 1;
            }

            tiebreaker = tiebreaker * 100 + values[&line.as_bytes()[idx]] as u64;
        }

        let mut signature = counts.values().map(|a| *a).collect::<Vec<_>>();
        signature.sort_by(|a, b| b.cmp(a));
        signature[0] += jokers;

        (mapping[&signature], tiebreaker)
    }

}

struct Hand {
    cards: String,
    score: u64,
    rank: Rank,
    tiebreaker: u64,
}

impl Hand {

    fn parse(line: &str, mapping: &HashMap<Vec<i32>, Rank>, values: &HashMap<u8, i32>) -> Hand {
        let (cards, score) = line.split_once(' ').unwrap();
        let (rank, tiebreaker) = Rank::parse(cards, mapping, values);
        Hand{cards: String::from(cards), score: score.parse::<u64>().unwrap(), rank, tiebreaker}
    }

}

fn main() {
    let mapping = Rank::mapping();
    let card_values = Rank::card_values();

    let mut hands = read_to_string("input.txt").unwrap().lines().map(|line| {
        Hand::parse(line, &mapping, &card_values)
    }).collect::<Vec<_>>();

    hands.sort_by(|lhs, rhs| {
        if lhs.rank == rhs.rank {
            return lhs.tiebreaker.cmp(&rhs.tiebreaker);
        }
        lhs.rank.cmp(&rhs.rank)
    });

    let mut score_base = 1;
    let mut points = 0;
    for hand in &hands {
        points += score_base * hand.score;
        score_base += 1;
    }

    println!("Total points: {}", points);
}