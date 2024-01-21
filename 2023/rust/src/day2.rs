pub fn part1() {
    println!(
        "{}",
        include_str!("../../inputs/day-2")
            .trim()
            .split('\n')
            .filter_map(|l| {
                let items = l.split(':').collect::<Vec<&str>>();
                let game_id: u32 = items[0].split(' ').nth(1).unwrap().parse().unwrap();
                let is_valid = items[1].split(|i| i == ',' || i == ';').any(|i| {
                    let split: Vec<&str> = i.split(' ').collect();
                    let num: u32 = split[1].parse().unwrap();
                    match split[2] {
                        "red" if num > 12 => {
                            return true;
                        }
                        "green" if num > 13 => {
                            return true;
                        }
                        "blue" if num > 14 => {
                            return true;
                        }
                        _ => return false,
                    }
                });

                if is_valid {
                    None
                } else {
                    Some(game_id)
                }
            })
            .sum::<u32>()
    )
}
