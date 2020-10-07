function divideAB(A, B){
    return 1 + divideAB(A-B, B)
}

let array = [];
function binarySearch(array,item){
    let middle = array[array.length/2];
    if (middle == item){
        return middle;
    }
    if(item > middle){
        array = array.slice(middle+1, array.length-1)
        binarySearch(array, item);
    }
    if(item < middle){
        array = array.slice(0, middle-1);
        binarySearch(array, item);
    }
}