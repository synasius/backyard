macro_rules! wow {
    (
        $(
            $x:expr; [ $( $y:expr ),* ]
        );*
    ) => {
        &[ $($( $x * $y ),*),*  ]
    }

}

fn main() {
    let a: &[i32]
        = wow!(5; [1, 2, 3, 4];
               6; [5, 6, 7, 8]);

    assert_eq!(a, [5, 10, 15, 20, 30, 36, 42, 48]);
}
