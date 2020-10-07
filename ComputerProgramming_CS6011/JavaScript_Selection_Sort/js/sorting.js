function swap(i, j) {
    var temp = i;
    i = j;
    j = temp;
}

function compare(a,b){
    return a < b;
}

function MinIndex(array, start, cmp){
    var minIndex = start;
    for (var i = start + 1; i < array.length; i++){
        if (cmp(array[i], array[minIndex])){
            minIndex = i;
        }
    }
    return minIndex;
}

function SelectionSort(array, cmp) {
    for (var i = 0; i < array.length - 1; i++) {
        var min = MinIndex(array, i, cmp);
        var a = array[i];
        array[i] = array[min];
        array[min] = a;
    }
    return array;
}

var a = [10,7,2,5,1,11,3,6,9,12];
var b = ["f", "F", "go", "alright", "Zebra"];

//SelectionSort(a);
console.log(SelectionSort(b, compare));


