// For Loop
for (let i = 0; i < 5; i++) {
    console.log(i);
}

// While Loop
let i = 0;
while (i < 5) {
    console.log(i);
    i++;
}

// Do While Loop
let j = 0;
do {
    console.log(j);
    j++;
} while (j < 5);


// For-of Loop (used for iterating over iterable objects like arrays)
const array = [10, 20, 30, 40, 50];
for (let number of array) {
    console.log(number);
}

// For-in Loop (used for iterating over the properties of an object)
const person = {
    name: "John",
    age: 30,
    city: "New York"
};

for (let key in person) {
    console.log(key , ":", person[key]);
}