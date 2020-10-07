#pragma checksum "/Users/derekolson/DerekOlson/CS6016/Project/phase3/LMS_handout/LMS_handout/LMS/Views/Student/Index.cshtml" "{ff1816ec-aa5e-4d10-87f7-6f4963833460}" "4939121cac2c552bfe78546cd1cc6bab4bf9823f"
// <auto-generated/>
#pragma warning disable 1591
[assembly: global::Microsoft.AspNetCore.Razor.Hosting.RazorCompiledItemAttribute(typeof(AspNetCore.Views_Student_Index), @"mvc.1.0.view", @"/Views/Student/Index.cshtml")]
[assembly:global::Microsoft.AspNetCore.Mvc.Razor.Compilation.RazorViewAttribute(@"/Views/Student/Index.cshtml", typeof(AspNetCore.Views_Student_Index))]
namespace AspNetCore
{
    #line hidden
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Threading.Tasks;
    using Microsoft.AspNetCore.Mvc;
    using Microsoft.AspNetCore.Mvc.Rendering;
    using Microsoft.AspNetCore.Mvc.ViewFeatures;
#line 1 "/Users/derekolson/DerekOlson/CS6016/Project/phase3/LMS_handout/LMS_handout/LMS/Views/_ViewImports.cshtml"
using Microsoft.AspNetCore.Identity;

#line default
#line hidden
#line 2 "/Users/derekolson/DerekOlson/CS6016/Project/phase3/LMS_handout/LMS_handout/LMS/Views/_ViewImports.cshtml"
using LMS;

#line default
#line hidden
#line 3 "/Users/derekolson/DerekOlson/CS6016/Project/phase3/LMS_handout/LMS_handout/LMS/Views/_ViewImports.cshtml"
using LMS.Models;

#line default
#line hidden
#line 4 "/Users/derekolson/DerekOlson/CS6016/Project/phase3/LMS_handout/LMS_handout/LMS/Views/_ViewImports.cshtml"
using LMS.Models.AccountViewModels;

#line default
#line hidden
#line 5 "/Users/derekolson/DerekOlson/CS6016/Project/phase3/LMS_handout/LMS_handout/LMS/Views/_ViewImports.cshtml"
using LMS.Models.ManageViewModels;

#line default
#line hidden
    [global::Microsoft.AspNetCore.Razor.Hosting.RazorSourceChecksumAttribute(@"SHA1", @"4939121cac2c552bfe78546cd1cc6bab4bf9823f", @"/Views/Student/Index.cshtml")]
    [global::Microsoft.AspNetCore.Razor.Hosting.RazorSourceChecksumAttribute(@"SHA1", @"363c4fd446cecdc21217d95f921ea2b5901a3ca3", @"/Views/_ViewImports.cshtml")]
    public class Views_Student_Index : global::Microsoft.AspNetCore.Mvc.Razor.RazorPage<dynamic>
    {
        #pragma warning disable 1998
        public async override global::System.Threading.Tasks.Task ExecuteAsync()
        {
            BeginContext(0, 2, true);
            WriteLiteral("\r\n");
            EndContext();
#line 2 "/Users/derekolson/DerekOlson/CS6016/Project/phase3/LMS_handout/LMS_handout/LMS/Views/Student/Index.cshtml"
  
  ViewData["Title"] = "StudentHome";
  Layout = "~/Views/Shared/StudentLayout.cshtml";

#line default
#line hidden
            BeginContext(98, 539, true);
            WriteLiteral(@"
<h4 id=""StudentInfo""></h4>
<h4 id=""Major""></h4>
<h4 id=""GPA""></h4>

<div class=""col-md-12"">
  <h4>My Classes</h4>
  <table id=""tblClasses"" class=""table table-bordered table-striped table-responsive table-hover"">
    <thead>
      <tr>
        <th align=""left"" class=""productth"">Course</th>
        <th align=""left"" class=""productth"">Name</th>
        <th align=""left"" class=""productth"">Semester</th>
        <th align=""left"" class=""productth"">Grade</th>
      </tr>
    </thead>
    <tbody></tbody>
  </table>
</div>

");
            EndContext();
            DefineSection("Scripts", async() => {
                BeginContext(658, 142, true);
                WriteLiteral("\r\n  <script type=\"text/javascript\">\r\n\r\n    LoadData();\r\n\r\n    function LoadData() {\r\n\r\n\r\n      $.ajax({\r\n        type: \'POST\',\r\n        url: \'");
                EndContext();
                BeginContext(801, 31, false);
#line 37 "/Users/derekolson/DerekOlson/CS6016/Project/phase3/LMS_handout/LMS_handout/LMS/Views/Student/Index.cshtml"
         Write(Url.Action("GetUser", "Common"));

#line default
#line hidden
                EndContext();
                BeginContext(832, 53, true);
                WriteLiteral("\',\r\n        dataType: \'json\',\r\n        data: { uid: \'");
                EndContext();
                BeginContext(886, 18, false);
#line 39 "/Users/derekolson/DerekOlson/CS6016/Project/phase3/LMS_handout/LMS_handout/LMS/Views/Student/Index.cshtml"
                 Write(User.Identity.Name);

#line default
#line hidden
                EndContext();
                BeginContext(904, 886, true);
                WriteLiteral(@"' },
        success: function (data, status) {

          if (data.success == false) {
            alert(""An error occured when loading user's information"");
          }
          else {
            StudentInfo.innerText = data.fname + "" "" + data.lname + ""    "" + data.uid;
            Major.innerText = ""Major: "" + data.department;
          }
        },
        error: function (ex) {
          var r = jQuery.parseJSON(response.responseText);
          alert(""Message: "" + r.Message);
          alert(""StackTrace: "" + r.StackTrace);
          alert(""ExceptionType: "" + r.ExceptionType);
        }
      });

      var tbl = document.getElementById(""tblClasses"");
      var body = tbl.getElementsByTagName(""tbody"")[0];
      tbl.removeChild(body);

      var newBody = document.createElement(""tbody"");


      $.ajax({
        type: 'POST',
        url: '");
                EndContext();
                BeginContext(1791, 31, false);
#line 67 "/Users/derekolson/DerekOlson/CS6016/Project/phase3/LMS_handout/LMS_handout/LMS/Views/Student/Index.cshtml"
         Write(Url.Action("GetGPA", "Student"));

#line default
#line hidden
                EndContext();
                BeginContext(1822, 53, true);
                WriteLiteral("\',\r\n        dataType: \'json\',\r\n        data: { uid: \'");
                EndContext();
                BeginContext(1876, 18, false);
#line 69 "/Users/derekolson/DerekOlson/CS6016/Project/phase3/LMS_handout/LMS_handout/LMS/Views/Student/Index.cshtml"
                 Write(User.Identity.Name);

#line default
#line hidden
                EndContext();
                BeginContext(1894, 463, true);
                WriteLiteral(@"' },
        success: function (data, status) {

          GPA.innerText = ""GPA: "" + Number.parseFloat(data.gpa).toFixed(1);

        },
        error: function (ex) {
          var r = jQuery.parseJSON(response.responseText);
          alert(""Message: "" + r.Message);
          alert(""StackTrace: "" + r.StackTrace);
          alert(""ExceptionType: "" + r.ExceptionType);
        }
        });


      $.ajax({
        type: 'POST',
        url: '");
                EndContext();
                BeginContext(2358, 37, false);
#line 86 "/Users/derekolson/DerekOlson/CS6016/Project/phase3/LMS_handout/LMS_handout/LMS/Views/Student/Index.cshtml"
         Write(Url.Action("GetMyClasses", "Student"));

#line default
#line hidden
                EndContext();
                BeginContext(2395, 53, true);
                WriteLiteral("\',\r\n        dataType: \'json\',\r\n        data: { uid: \'");
                EndContext();
                BeginContext(2449, 18, false);
#line 88 "/Users/derekolson/DerekOlson/CS6016/Project/phase3/LMS_handout/LMS_handout/LMS/Views/Student/Index.cshtml"
                 Write(User.Identity.Name);

#line default
#line hidden
                EndContext();
                BeginContext(2467, 1503, true);
                WriteLiteral(@"' },
        success: function (data, status) {

          //alert(JSON.stringify(data));

          $.each(data, function (i, item) {

            var tr = document.createElement(""tr"");

            var td = document.createElement(""td"");
            td.appendChild(document.createTextNode(item.subject + item.number));
            tr.appendChild(td);

            var td = document.createElement(""td"");
            var a = document.createElement(""a"");
            a.setAttribute(""href"", ""/Student/Class/?subject="" + item.subject + ""&num="" + item.number + ""&season="" + item.season + ""&year="" + item.year);
            a.appendChild(document.createTextNode(item.name));
            td.appendChild(a);
            tr.appendChild(td);

            var td = document.createElement(""td"");
            td.appendChild(document.createTextNode(item.season + "" "" + item.year ));
            tr.appendChild(td);

            var td = document.createElement(""td"");
            td.appendChild(document.createText");
                WriteLiteral(@"Node(item.grade));
            tr.appendChild(td);

            newBody.appendChild(tr);

          });

          tbl.appendChild(newBody);

        },
        error: function (ex) {
          var r = jQuery.parseJSON(response.responseText);
          alert(""Message: "" + r.Message);
          alert(""StackTrace: "" + r.StackTrace);
          alert(""ExceptionType: "" + r.ExceptionType);
        }
        });


      return false;
    }



  </script>

");
                EndContext();
            }
            );
        }
        #pragma warning restore 1998
        [global::Microsoft.AspNetCore.Mvc.Razor.Internal.RazorInjectAttribute]
        public global::Microsoft.AspNetCore.Mvc.ViewFeatures.IModelExpressionProvider ModelExpressionProvider { get; private set; }
        [global::Microsoft.AspNetCore.Mvc.Razor.Internal.RazorInjectAttribute]
        public global::Microsoft.AspNetCore.Mvc.IUrlHelper Url { get; private set; }
        [global::Microsoft.AspNetCore.Mvc.Razor.Internal.RazorInjectAttribute]
        public global::Microsoft.AspNetCore.Mvc.IViewComponentHelper Component { get; private set; }
        [global::Microsoft.AspNetCore.Mvc.Razor.Internal.RazorInjectAttribute]
        public global::Microsoft.AspNetCore.Mvc.Rendering.IJsonHelper Json { get; private set; }
        [global::Microsoft.AspNetCore.Mvc.Razor.Internal.RazorInjectAttribute]
        public global::Microsoft.AspNetCore.Mvc.Rendering.IHtmlHelper<dynamic> Html { get; private set; }
    }
}
#pragma warning restore 1591
