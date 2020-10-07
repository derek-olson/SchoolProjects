
let selectedStates = [];
let globalData;
const covidData = d3.csv("us-states.csv", d3.autoType).then(function (covidData) 
{
    globalData = covidData;
    console.log("covidData", covidData);
    let states = new Set(covidData.map(d => d.state));
    let stateList = Array.from(states);
    stateList.sort();
    makeStateList(stateList);
    loadMap();
});

function makeStateList(stateList, data) 
{
    d3.select('#stateDiv').selectAll('p')
        .data(stateList)
        .join(
            enter => {
                enter.append('p')
                    .text((d, i) => d)
                    .attr("id", d => `${d}`)
                    .on("click", handleClick);
            }
        );
}

function loadMap() {
    let svg = d3.select("#USMap");
    let path = d3.geoPath();
    d3.json("states-albers-10m.json", d3.autoType()).then(function (us) {
        //console.log("objectssssss" , us.objects.states);
        //console.log(topojson.feature(us, us.objects.states).features)
        svg.append("g")
            .attr("class", "states")
            //.attr("id", function (d) {console.log(d)})//return us.objects.states.geometries[d].properties.name})
            .selectAll("path")
            .data(topojson.feature(us, us.objects.states).features)
            .enter().append("path")
            .attr("d", path)
            .on("click", clickState);

        svg.append("path")
            .attr("class", "state-borders")
            .attr("d", path(topojson.mesh(us, us.objects.states, function (a, b) {
                return a !== b;
            })));
    });
}

function clickState(d,i){
    let toSelect = d.properties.name;
    console.log("toSelect", toSelect);

    //clear the selection from the state list 
    if(selectedStates.length > 0)
    {
        let toRemove = selectedStates[0].name;
        console.log("state to remove", toRemove);
        $(`#${toRemove}`).removeClass("selected");
        selectedStates.pop();
    }

    //add selected to corresponding state in list
    $(`#${toSelect}`).addClass("selected");
    let stateData = {};
    stateData.name = toSelect;
    selectedStates.push(stateData);

    $("#lineChart").empty();

    getFilteredData();
}

function handleClick(d, i){
    console.log(d,i);
    let elem = d3.select(this);
    elem.classed("selected", () => !d3.select(this).classed("selected"));
    if(elem.classed("selected")){
        if (selectedStates.length === 1) {
            let toRemove = selectedStates[0].name;
            console.log("state to remove", toRemove);
            $(`#${toRemove}`).removeClass("selected");
            selectedStates.pop();
        }
        let stateData = {};
        stateData.name = d;
        selectedStates.push(stateData);
        console.log("selected state: ", selectedStates[0].name);
    }
    else {
        selectedStates = selectedStates.filter( x => x.name != d);
        console.log("a state was unselected", selectedStates[0]);
    }

    $("#lineChart").empty();

    getFilteredData();
}

function getFilteredData() {
    let state = selectedStates[0].name;
    let filteredData = globalData.filter(function(d) { return d.state == state; });
    console.log(filteredData);
    
    lineChart(filteredData);
}

function lineChart(data){

    var margin = {top: 10, right: 30, bottom: 30, left: 60},
    width = 1000 - margin.left - margin.right,
    height = 235 - margin.top - margin.bottom;

    var svg = d3.select("#lineChart")
        .append("svg")
        .attr("width", width + margin.left + margin.right)
        .attr("height", height + margin.top + margin.bottom)
        .append("g")
        .attr("transform","translate(" + margin.left + "," + margin.top + ")"
    );

    var x = d3.scaleTime()
      .domain(d3.extent(data, function(d) { return d.date; }))
      .range([ 0, width ]);
    svg.append("g")
      .attr("transform", "translate(0," + height + ")")
      .call(d3.axisBottom(x));

    var y = d3.scaleLinear()
      .domain([0, d3.max(data, function(d) { return +d.deaths; })])
      .range([ height, 0 ]);
    svg.append("g")
      .call(d3.axisLeft(y));

    svg.append("path")
    .datum(data)
    .attr("fill", "none")
    .attr("stroke", "steelblue")
    .attr("stroke-width", 1.5)
    .attr("d", d3.line()
    .x(function(d) { return x(d.date) })
    .y(function(d) { return y(d.deaths) })
    );

    svg.append("text")
        .attr("x", 20)
        .attr("y", 20)
        .attr("font-size", "20px")
        .text(`Number of deaths in ${selectedStates[0].name}`)
}


