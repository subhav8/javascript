/*
 * kruskal's Algorithm to find MST
 *
 */

function same_tree(trie1, trie2) {
    var same = false;
    if (trie1[0].length != trie2[0].length) {
        return same;
    }
    if (trie1[0].length == trie2[0].length){
        for (i=0; i< trie1[0].length; i++) {
            if(trie1[0][i] != trie2[0][i])
                return same;
        }
        return true;
    }
}

function arraysEqual(arr1, arr2) {
    if(arr1.length != arr2.length)
        return false;
    for(var i = arr1.length; i--;) {
        if(arr1[i] != arr2[i])
            return false;
    }

    return true;
}

function without(arr, first_subset, second_subset) {

    var merge1 = [].concat.apply([],first_subset)
        var merge2 = [].concat.apply([],second_subset)

        for (var j = arr.length; j--;) {
            var res = arraysEqual(arr[j], merge1)
                if(res == true) {
                    arr.splice(j,1)
                } 
        }
    for (var j = arr.length; j--;) {
        var res = arraysEqual(arr[j], merge2)
            if(res == true) {
                arr.splice(j,1)
            } 
    }
}
function mst(arr) {
    var vertices = ["house", "temple", "petrol-bunk", "shopping-mall", "college"];
    var edges= [
        ["house", "temple", 6], ["house", "shopping-mall", 5],
        ["shopping-mall", "temple", 6], ["temple", "petrol-bunk", 9], ["petrol-bunk", "college", 9],
        ["shopping-mall", "petrol-bunk", 1],
        ["temple", "college", 2]];

    //var mapping = ["","house","temple","shopping-mall", "petrol-bunk", "college"];

    var minimum_spanning_tree = [];
    var mirror_vertices = vertices.map(function(node) { return [node]; });

    /* Sort the array by weight attribute */
    var sorted_edges = edges.sort(function(edge1, edge2) {return  edge1[2] - edge2[2]});
    /* array sorted in reverse order due to push operation. The lowest value will be in bottom of the array
     * Just like stack push 
     */
    sorted_edges.reverse()
        //console.log(sorted_edges)

        while ( mirror_vertices.length > 1 ) {

            /*Remove the edge with minimum weight */

            var e = sorted_edges.pop();

            //console.log(e);
            var vertex1 = e[0];

            var vertex2 = e[1];

            /* Return the list which has vertex1 in it */

            //console.log("mirror vertices")
            //console.log(mirror_vertices)
            var tree1 = mirror_vertices.filter(function(vert) {return vert.includes(vertex1)});
            //console.log("tree1")
            //    console.log(tree1)
                /* Return the list which has vertex2 in it */

            var tree2 = mirror_vertices.filter(function(vert) {return vert.includes(vertex2)});

            //console.log("tree2")
             //   console.log(tree2)
                /* Only when the sets are different, trying using disjoint-set method to span the forest */

                if (same_tree(tree1,tree2) == false) {
                    /* returns an array without containing the vertex*/
                    without(mirror_vertices, tree1, tree2);
                    //console.log(mirror_vertices)
                    mirror_vertices.push(tree1[0].concat(tree2[0]));
                    //console.log(mirror_vertices);
                    minimum_spanning_tree.push(e);
                }
        }
    //alert("Calculated Spanning Tree!!");
    //alert(minimum_spanning_tree);
    //console.log(minimum_spanning_tree);
    return;
}

mst()




