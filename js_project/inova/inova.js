function getDevices(){
    //var url = "http://localhost:8080/devices";
    var url = "http://146.11.25.2:8010/device";
    $.getJSON(url, function(result) {
            var devices = result;
            showDevices(devices);
            });
}

function getDockerImages(){
    var url = "http://146.11.25.2:8010/image";
    $.getJSON(url, function(result) {
            console.log(result);
            var dockerimages= result;
            showDockerImages(dockerimages);
            });
}

function deleteImage(imageName){
    $.ajax({ url: "http://146.11.25.2:8010/image/" + imageName, 
             type: "DELETE",
             crossDomain:true,
             success: function(result){ getDockerImages();}
    });
}

function addImage(){
    var obj = {"name":"albert2","uri":"docker://repository/branch/app/url","Config":"configuration string for application"};
    $.ajax({
        type: "POST",
        url: "http://146.11.25.2:8010/image",
        dataType: "json",
        data: JSON.stringify(obj),
        success: function(result) {
            getDockerImages();
            },
        error: function(xhr){
            console.log("Fail:" + xhr.message);
            }
    });
}

function showDevices(devices){
    for (var i=0;i<devices.length;i++){
        var hwinfoTab = "hwinfo_"+devices[i].name;
        var imgTab = "images_"+devices[i].name; 
        var devicesHtml = '<div id="'+ devices[i].uuid +'" class="col-xs-3 col-sm-3 col-lg-3 panel panel-info'; if(i>0) devicesHtml += ' col-md-offset-1">';
        else devicesHtml += '">';
        devicesHtml += '<div class="panel-heading"><h3 class="panel-title">'+ devices[i].name +'</h3></div>' +
            '<table class="table table-striped"><tbody>'+
            '<tr class="row"><td class="col-xs-4 col-sm-4 col-lg-4">UUID</td><td class="col-xs-8 col-sm-8 col-lg-8">' + devices[i].uuid + '</td></tr>' +
            '</tbody></table>' +
            '<ul class="nav nav-tabs" role="tablist"><li role="presentation" class="active"><a href="#' + hwinfoTab +'" role="tab" aria-controls="'+hwinfoTab +'" aria-expanded="true">HWInfo</a></li><li role="presentation"><a href="#' + imgTab +'" role="tab">Images</a></li></ul>' +
            '<div class="tab-content">'+
            '<div id="' + hwinfoTab +'" class="tab-pane fade active in" role="tabpanel" aria-labelledby="' + hwinfoTab +'-tab">'+
            '<table class="table table-striped"><tbody>'+
            '<tr class="row"><td class="col-xs-4 col-sm-4 col-lg-4">Host:</td><td class="col-xs-8 col-sm-8 col-lg-8">' + devices[i]["HWInfo"].address.host + '</td></tr>' +
            '<tr class="row"><td class="col-xs-4 col-sm-4 col-lg-4">Ports:</td> <td class="col-xs-8 col-sm-8 col-lg-8">' + devices[i]["HWInfo"].address.port + '</td></tr>' +
            '<tr class="row"><td class="col-xs-4 col-sm-4 col-lg-4">RAM:</td> <td class="col-xs-8 col-sm-8 col-lg-8">' + devices[i]["HWInfo"].capacity.ram + '</td></tr>' +
            '<tr class="row"><td class="col-xs-4 col-sm-4 col-lg-4">CPU:</td> <td class="col-xs-8 col-sm-8 col-lg-8">' + devices[i]["HWInfo"].capacity.cpu + '</td></tr>' +
            '</tbody></table>'+
            '</div>'+
            '<div id="' + imgTab + '" class="tab-pane fade" role="tabpanel" aria-labelledby="' + imgTab + '-tab">'+
            '<div class="row"><div class="col-xs-12">'+ dockersHtml(devices[i].Images) + '</div></div>'+
            '</div>'+
            '</div>'+
            '</div>';
        $("#devicesContainer").append(devicesHtml);
    }

    $('.nav-tabs a').click(function(e){ e.preventDefault();$(this).tab('show')});
}

function dockersHtml(dockers){
    var dockersTable = '<table class="table"><caption class="text-left"><h4>Docker Images</h4></caption><thead><tr><th>#</th><th>Name</th><th>URL</th><th>Config</th><th></th></tr></thead>';
    dockersTable += '<tbody class="docimgs">';
    var i=1;
    for(var j in dockers){
        dockersTable += '<tr><td>'+ (i++) +'</td><td>'+ dockers[j].name +'</td><td>'+ dockers[j].url +'</td><td>'+ dockers[j].Config +'</td><td><button class="img-op-btn" data-toggle="modal" data-target="#myModal" type="button"><span class="glyphicon glyphicon-cog"></span></button></td></tr>';
    }
    dockersTable += '<tr ondragover="allowDrop(event)" ondrop="drop(event)"><td colspan="5"><button type="button" class="btn btn-default btn-lg"><span class="glyphicon glyphicon-plus-sign"> Drag to add docker images</span></button></td></tr>';
    dockersTable += '</tbody></table>';
    return dockersTable;
}

function showDockerImages(dockerimages){
    for (var i=0;i<dockerimages.length;i++){
        var htmlText = '<div id="'+ dockerimages[i].name+'" class="col-xs-3 col-sm-3 col-lg-3 panel panel-danger ';
        if(i>0) htmlText += 'col-md-offset-1" draggable="true" ondragstart="drag(event)">';
        else htmlText += '" draggable="true" ondragstart="drag(event)">';
        htmlText += '<div class="panel-heading"><h3 class="panel-title">'+ dockerimages[i].name+'</h3></div>'+
            '<table class="table table-striped table-bordered"><tbody>'+
            '<tr class="row"><td class="col-xs-4 col-sm-4 col-lg-4">URL</td><td class="col-xs-8 col-sm-8 col-lg-8">' + dockerimages[i].uri + '</td></tr>' +
            '<tr class="row"><td class="col-xs-4 col-sm-4 col-lg-4">Config</td><td class="col-xs-8 col-sm-8 col-lg-8">' + dockerimages[i].Config + '</td></tr>' +
            '</tbody></table>'+ 
            '</div>';
        $("#dockerimagesContainer").append(htmlText);
    }
}

function creatModalForm(){

}
