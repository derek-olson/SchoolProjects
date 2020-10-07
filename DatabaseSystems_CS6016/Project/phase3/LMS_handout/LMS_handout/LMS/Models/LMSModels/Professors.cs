using System;
using System.Collections.Generic;

namespace LMS.Models.LMSModels
{
    public partial class Professors
    {
        public Professors()
        {
            Classes = new HashSet<Classes>();
        }

        public int ProfessorId { get; set; }
        public string UId { get; set; }
        public string Dept { get; set; }

        public virtual Departments DeptNavigation { get; set; }
        public virtual Users U { get; set; }
        public virtual ICollection<Classes> Classes { get; set; }
    }
}
