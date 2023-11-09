# Features

## Variables

Variable assignment is done with the `let` keyword.

```cashew
let number = 1
let word = "hello"
```

### Mutability

In Cashew, variables are immutable by default, but can be made mutable with the `mut` keyword.

```cashew
let mut number = 1
number = 2
```

### Constants

Constants are immutable variables that are always declared with a type, they are evaluated at compile time.

```cashew
const number: i32 = 1
```

### Basic Data Types

Like some other languages, Cashew has explicit sizes for integers and floats.

#### Signed Integers

- `i8`: 8-bit signed integer
- `i16`: 16-bit signed integer
- `i32`: 32-bit signed integer
- `i64`: 64-bit signed integer
- `isize`: native signed integer (32-bit on 32-bit systems, 64-bit on 64-bit systems)

#### Unsigned Integers

- `u8`: 8-bit unsigned integer
- `u16`: 16-bit unsigned integer
- `u32`: 32-bit unsigned integer
- `u64`: 64-bit unsigned integer
- `usize`: native unsigned integer (32-bit on 32-bit systems, 64-bit on 64-bit systems)

#### Floating Point

- `f32`: 32-bit floating point
- `f64`: 64-bit floating point
