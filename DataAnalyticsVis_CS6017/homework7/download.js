let requestUrl = "https://covid19-lake.s3.us-east-2.amazonaws.com/rearc-covid-19-nyt-data-in-usa/csv/us-states/us-states.csv";

var today = new Date();
var dd = String(today.getDate()).padStart(2, '0');
var mm = String(today.getMonth() + 1).padStart(2, '0'); 
var yyyy = today.getFullYear();
today = mm + '_' + dd + '_' + yyyy;

let path = '/Users/derekolson/DerekOlson/CS6017/homework7/';
let file_name = 'us_states_'+today+'.csv';
let out_name = path+file_name;
let test_file = new File([],out_name);



let xhr = new XMLHttpRequest();
xhr.open("GET", requestUrl);
xhr.responseType = "blob";

xhr.onload = function () {
    saveData(this.response, file_name); 
};
xhr.send();

function saveData(blob, fileName)
{
    let a = document.createElement("a");
    document.body.appendChild(a);
    a.style = "display: none";

    let url = window.URL.createObjectURL(blob);
    a.href = url;
    a.download = fileName;
    a.click();
    window.URL.revokeObjectURL(url);
}

// $.ajax({ 
//     url: requestUrl,
//     processData: false,
//     dataType: 'text'
// }).done(function(data) {
//     var blob = new Blob([data], { type: "text/plain; encoding=utf8" });
//     saveData(blob, out_name);    
// });


function fileExists(url) {
    if(url){
        var req = new XMLHttpRequest();
        req.open('HEAD', url, false);
        req.send();
        return true;
    } else {
        return false;
    }
}