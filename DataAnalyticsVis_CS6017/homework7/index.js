//adapted from https://observablehq.com/@d3/bar-chart-race

d3.csv("/us-states.csv", d3.autoType).then(function (data) {
  console.log("data", data);

  let states = new Set(data.map(d => d.state));
  console.log("states", states);

  let duration = 250;

  let n = 55;

  let k = 1;

  let datevalues = Array.from(d3.rollup(data, ([d]) => d.cases, d => +d.date, d => d.state)).map(([date, data]) => [new Date(date), data]).sort(([a], [b]) => d3.ascending(a, b));

  let kf = keyframes(datevalues, states, k);

  let nameframes = d3.groups(kf.flatMap(([, data]) => data), d => d.state);

  let prev = new Map(nameframes.flatMap(([, data]) => d3.pairs(data, (a, b) => [b, a])));

  let next = new Map(nameframes.flatMap(([, data]) => d3.pairs(data)));

  let barSize = 25;

  let margin = ({ top:2, right: 6, bottom: 6, left: 0 });

  let height = margin.top + barSize * (n*2) + margin.bottom;

  let width = margin.left + barSize * n + margin.right;

  let x = d3.scaleLinear([0, 1], [margin.left, width - margin.right]);
  let x2 = d3.scaleLinear().domain([0,300000]).range([5,500]);

  let y = d3.scaleBand().domain(d3.range(n + 1)).rangeRound([margin.top, margin.top + barSize * (100 + 1 + 0.1)]).padding(0.1);

  chart(kf, duration, height, width, prev, next, x, y, margin, barSize, x2);
});


async function chart(keyframes, duration, height, width, prev, next, x, y, margin, barSize, x2)
{
  const svg = d3.create("svg:svg").attr("viewBox", [0, 0, width, height]);

  const updateBars = bars(svg, prev, next, x, y, x2);
  const updateAxis = axis(svg, x, y, margin, width, barSize);
  const updateLabels = labels(svg, x2, y, prev);
  const updateDisplayDates = displayDates(keyframes,svg, barSize, width, margin);
  console.log("svg", svg.node());
  //yield svg.node();

  d3.select("#chart").append(() => svg.node());

  for(let keyframe of keyframes) {
    const transition = svg.transition().duration(duration).ease(d3.easeLinear);

    // Extract the top bar’s value.
    x.domain([0, keyframe[1][0].value]);

    updateAxis(keyframe, transition);
    updateBars(keyframe, transition);
    updateLabels(keyframe, transition);
    updateDisplayDates(keyframe, transition);

    //svg.interrupt();

    await transition.end();
  }
}

function rank(value, states) 
{
    const data = Array.from(states, state => ({ state, cases: value(state) }));
    data.sort((a, b) => d3.descending(a.cases, b.cases));
    for (let i = 0; i < data.length; i++) 
    {
        data[i].rank = i;
    }
    return data;
}

function keyframes(datevalues, states, k) 
{
    const keyframes = [];
    let ka, a, kb, b;
    for([[ka, a], [kb, b]] of d3.pairs(datevalues)) 
    {
        for (let i = 0; i < k; ++i) 
        {
            const t = i / k;
            keyframes.push([
                new Date(ka * (1 - t) + kb * t),
                rank(state => (a.get(state) || 0) * (1 - t) + (b.get(state) || 0) * t, states)
            ]);
        }
    }   
    keyframes.push([new Date(kb), rank(state => b.get(state) || 0, states)]);
    return keyframes;
}   

function bars(svg, prev, next, x, y, x2) 
{
  let bar = svg.append("g").attr("fill-opacity", 0.6).selectAll("rect");
  let bw = y.bandwidth();
  let _x = x(0);
  return ([date, data], transition) => bar = bar
      .data(data.slice(0, 55), d => d.state)
      .join(
          enter => enter.append("rect")
              .attr("fill", function(d) {return color(d)})
              .attr("height", bw)
              .attr("x", _x)
              .attr("y", d => y((prev.get(d) || d).rank))
              .attr("width", function(d){return x(prev.get(d.cases))}),
          update => update.attr("fill", function(d) {return color(d)}),
          exit => exit.transition(transition).remove()
              .attr("y", d => y((next.get(d) || d).rank))
              .attr("width", function(d){return x(next.get(d.cases))})
      )
      .call(bar => bar.transition(transition)
          .attr("y", d => y(d.rank))
          .attr("width", function(d){return x2(d.cases)}));
}

function labels(svg, x, y, prev) 
{
    let label = svg.append("g")
        .style("font", "bold 18px var(--sans-serif)")
        .style("font-variant-numeric", "tabular-nums")
        .selectAll("text");

    return ([date, data], transition) => label = label
        .data(data.slice(0, 55), d => d.state)
        .join(
            enter => enter.append("text")
                .attr("transform", d => `translate(${function(d){return x(prev.get(d.cases))}},${y((prev.get(d) || d).rank)})`)
                .attr("y", y.bandwidth() / 2)
                .attr("x", 5)
                .attr("dy", "-0.25em")
                .text(d => d.state)
                .call(text => text.append("tspan")
                    .attr("fill-opacity", 0.7)
                    .attr("font-weight", "normal")
                    .attr("x", 5)
                    .attr("dy", "1.15em")),
            update => update,
            exit => exit.transition(transition).remove()
                .attr("transform", d => `translate(${x((next.get(d) || d).cases)},${y((next.get(d) || d).rank)})`)
                .call(g => g.select("tspan").tween("text", d => textTween(d.cases, (next.get(d) || d).cases)))
        )
        .call(bar => bar.transition(transition)
            .attr("transform", d => `translate(${x(d.cases)},${y(d.rank)})`)
            .call(g => g.select("tspan").tween("text", d => textTween((prev.get(d) || d).cases, d.cases))));
}

function textTween(a, b) 
{
  let formatNumber = d3.format(",d");
  const i = d3.interpolateNumber(a, b);
  return function (t) 
  {
    this.textContent = formatNumber(i(t));
  };
}

function displayDates(kf, svg, barSize, width, margin) 
{
  let formatDate = d3.utcFormat("%B %d, %Y");
  let d = d3.select("#date");
  
  const now = d.append("text")
      .style("font", `bold ${barSize}px var(--sans-serif)`)
      .style("font-variant-numeric", "tabular-nums")
      .attr("text-anchor", "end")
      .attr("x", width - 6)
      .attr("y", margin.top + barSize * (55 - 0.45))
      .attr("dy", "0.32em")
      .text(formatDate(kf[0][0]));
return ([date], transition) => 
  {
      transition.end().then(() => now.text(formatDate(date)));
  };
  
}

function axis(svg, x, y, margin, width, barSize) 
{
  const g = svg.append("g")
      .attr("transform", `translate(0,${margin.top})`);

  const axis = d3.axisTop(x)
      .ticks(width / 160)
      .tickSizeOuter(0)
      .tickSizeInner(-barSize * (55 + y.padding()));

  return (_, transition) => 
  {
    g.transition(transition).call(axis);
    g.select(".tick:first-of-type text").remove();
    g.selectAll(".tick:not(:first-of-type) line").attr("stroke", "white");
    g.select(".domain").remove();
  };
}

function getRandomColor() 
{
  var letters = '0123456789ABCDEF'.split('');
  var color = '#';
  for (var i = 0; i < 6; i++ ) 
  {
       color += letters[Math.floor(Math.random() * 16)];
  }
  return color;
}

function color(d)
{
  if(d.rank < 3)
  {
    return "#FA0AEC"
  }
  else if (d.rank < 11)
  {
    return "#C70039"
  }
  else if(d.rank < 21)
  {
    return "#E1B708"
  }
  else if(d.rank < 31)
  {
    return "#F4ED0E"
  }
  else if(d.rank < 41)
  {
    return "#296305"
  }  
  else
  {
    return "#051465"
  }
}
