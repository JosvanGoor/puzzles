use std::{fs::read_to_string, collections::HashMap};

// don't judge it works

struct SeedRange {
    start: i64,
    length: i64
}

impl SeedRange {

    fn new(start: i64, length: i64) -> SeedRange {
        SeedRange{start: start, length: length}
    }

    fn contains(&self, input: i64) -> bool {
        (self.start..(self.start + self.length)).contains(&input)
    }

}

struct Range {
    source: i64,
    destination: i64,
    length: i64,
    delta: i64
}

impl Range {

    fn parse(line: &str) -> Range {
        let numbers = line.split(' ').map(|num| {
            num.parse::<i64>().unwrap()
        }).collect::<Vec<_>>();

        Range{source: numbers[1], destination: numbers[0], length: numbers[2], delta: numbers[0] - numbers[1]}
    }

    fn contains(&self, src: i64) -> bool {
        (self.source..(self.source+self.length)).contains(&src)
    }

    fn reverse_contains(&self, src: i64) -> bool {
        self.contains(src - self.delta)
    }

    fn reverse_map(&self, src: i64) -> i64 {
        src - self.delta
    }

}

struct Mapping {
    from: String,
    ranges: Vec<Range>
}

impl Mapping {

    fn new(from: &str) -> Mapping {
        Mapping{from: String::from(from), ranges: Vec::new()}
    }

    fn from_direction(line: &str) -> Mapping {
        let parts = line[0..line.find(' ').unwrap()].split('-').collect::<Vec<_>>();
        Mapping::new(parts[0])
    }

}

fn parse_seeds(line: &str) -> Vec<i64> {
    line[line.find(' ').unwrap() + 1..line.len()].split(' ').map(|num| {
        num.parse::<i64>().unwrap()
    }).collect::<Vec<_>>()
}

fn reverse_map_to_next(mapping: &Mapping, input: i64) -> i64 {
    for range in &mapping.ranges {
        if range.reverse_contains(input){ 
            return range.reverse_map(input);
        }
    }

    input
}

fn main() {
    let file = read_to_string("input.txt").unwrap();
    let mut lines = file.lines();

    // parse seeds
    let seeds = parse_seeds(lines.next().unwrap());
    lines.next().unwrap(); // skip empty line below seeds

    let mut mappings: HashMap<String, Mapping> = HashMap::new();

    loop {
        let line = match lines.next() {
            Some(line) => line,
            None => break
        };

        let mut mapping = Mapping::from_direction(line);

        // now we parse ranges
        loop {
            let line = match lines.next() {
                Some(line) => line,
                None => break
            };

            if line.is_empty() {
                break
            }

            mapping.ranges.push(Range::parse(line));
        }

        mapping.ranges.sort_by(|a, b| a.destination.cmp(&b.destination));
        mappings.insert(mapping.from.clone(), mapping);
    }

    let seed_to_soil = &mappings["seed"];
    let soil_to_fertilizer = &mappings["soil"];
    let fertilizer_to_water = &mappings["fertilizer"];
    let water_to_light = &mappings["water"];
    let light_to_temperature = &mappings["light"];
    let temperature_to_humidity = &mappings["temperature"];
    let humidity_to_location = &mappings["humidity"];

    let map_location_to_seed = |location: i64| {
        let humidity = reverse_map_to_next(humidity_to_location, location);
        let temperature = reverse_map_to_next(temperature_to_humidity, humidity);
        let light = reverse_map_to_next(light_to_temperature, temperature);
        let water = reverse_map_to_next(water_to_light, light);
        let fertilizer = reverse_map_to_next(fertilizer_to_water, water);
        let soil = reverse_map_to_next(soil_to_fertilizer, fertilizer);
        reverse_map_to_next(seed_to_soil, soil)
    };

    let seed_ranges = (0..(seeds.len() / 2)).map(|index| {
        let idx = index * 2;
        SeedRange::new(seeds[idx], seeds[idx + 1])
    }).collect::<Vec<_>>();

    let mut location = 0;
    loop {
        let seed = map_location_to_seed(location);

        for range in &seed_ranges {
            if range.contains(seed) {
                println!("Location: {}", location);
                return;
            }
        }

        location += 1;
    }
}