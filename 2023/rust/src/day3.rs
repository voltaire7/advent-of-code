// pub fn part1() {
//     let map = include_bytes!("../../inputs/day-3");
//     let width = map.iter().position(|b| b == &b'\n').unwrap() as isize;
//     println!(
//         "{}",
//         (0..map.len() - 2)
//             .filter(|i| {
//                 map[*i].is_ascii_digit()
//                     && !map.get(i.wrapping_sub(1)).map_or(false, u8::is_ascii_digit)
//             })
//             .map(|i| {
//                 let d = (i + 1..i + 4)
//                     .position(|i| !map[i].is_ascii_digit())
//                     .unwrap()
//                     + 1;
//                 (i, d as _, atoi::atoi::<usize>(&map[i..i + d]).unwrap())
//             })
//             .filter(|(i, d, _n)| {
//                 (-width - 2..-width + *d)
//                     .chain([-1, *d])
//                     .chain(width..width + *d + 2)
//                     .any(|j| {
//                         map.get((*i as isize + j) as usize)
//                             .map_or(false, |b| b != &b'.' && b.is_ascii_punctuation())
//                     })
//             })
//             .map(|(_i, _d, n)| n)
//             .sum::<usize>()
//     );
// }

pub fn part1() {
    let content = include_str!("../../inputs/day-3")
        .chars()
        .collect::<Vec<char>>();
    let width = content.iter().position(|x| x == &'\n').unwrap() as isize;
    println!(
        "{}",
        (0..content.len())
            .filter(|x| content[*x].is_ascii_digit()
                && !content
                    .get(x.wrapping_sub(1))
                    .map_or(false, char::is_ascii_digit))
            .map(|x| {
                let d = (x + 1..x + 4)
                    .position(|y| !content[y].is_ascii_digit())
                    .unwrap()
                    + 1;
                (
                    x,
                    d as isize,
                    content[x..x + d]
                        .to_vec()
                        .into_iter()
                        .collect::<String>()
                        .parse::<usize>()
                        .unwrap(),
                )
            })
            .filter(|(x, d, _n)| {
                (-width - 2..-width + *d)
                    .chain([-1, *d])
                    .chain(width..width + *d + 2)
                    .any(|y| {
                        content
                            .get((*x as isize + y) as usize)
                            .map_or(false, |z| z != &'.' && z.is_ascii_punctuation())
                    })
            })
            .map(|(_x, _d, n)| n)
            .sum::<usize>()
    );
}

pub fn part2() {
    let content = include_bytes!("../../inputs/day-3");
    let width = content.iter().position(|b| b == &b'\n').unwrap() as isize;
    let mut nums = vec![];
    println!(
        "{}",
        (0..content.len() - 2)
            .filter(|i| content[*i] == b'*')
            .filter_map(|i| {
                nums.clear();
                nums.extend(
                    (-width - 2..=-width)
                        .chain([-1, 1])
                        .chain(width..=width + 2)
                        .map(|pos| (i as isize + pos) as usize)
                        .filter(|pos| content[*pos].is_ascii_digit())
                        .flat_map(|pos| {
                            (pos.saturating_sub(2)..=pos)
                                .rev()
                                .take_while(|i| content[*i].is_ascii_digit())
                                .last()
                        }),
                );
                nums.dedup();
                (nums.len() == 2).then(|| {
                    nums.iter()
                        .map(|i| atoi::atoi::<usize>(&content[*i..*i + 3]).unwrap())
                        .product::<usize>()
                })
            })
            .sum::<usize>()
    );
}
