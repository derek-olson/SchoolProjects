using System;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata;

namespace LMS.Models.LMSModels
{
    public partial class Team12LMSContext : DbContext
    {
        public Team12LMSContext()
        {
        }

        public Team12LMSContext(DbContextOptions<Team12LMSContext> options)
            : base(options)
        {
        }

        public virtual DbSet<Administrators> Administrators { get; set; }
        public virtual DbSet<AssignmentCategories> AssignmentCategories { get; set; }
        public virtual DbSet<Assignments> Assignments { get; set; }
        public virtual DbSet<Classes> Classes { get; set; }
        public virtual DbSet<Courses> Courses { get; set; }
        public virtual DbSet<Departments> Departments { get; set; }
        public virtual DbSet<Enrollments> Enrollments { get; set; }
        public virtual DbSet<Professors> Professors { get; set; }
        public virtual DbSet<Students> Students { get; set; }
        public virtual DbSet<Submissions> Submissions { get; set; }
        public virtual DbSet<Users> Users { get; set; }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            if (!optionsBuilder.IsConfigured)
            {
#warning To protect potentially sensitive information in your connection string, you should move it out of source code. See http://go.microsoft.com/fwlink/?LinkId=723263 for guidance on storing connection strings.
                optionsBuilder.UseMySql("Server=atr.eng.utah.edu;User Id=u1275695;Password=456345;Database=Team12LMS");
            }
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<Administrators>(entity =>
            {
                entity.HasKey(e => e.AdminId)
                    .HasName("PRIMARY");

                entity.HasIndex(e => e.UId)
                    .HasName("uID");

                entity.Property(e => e.AdminId)
                    .HasColumnName("AdminID")
                    .HasColumnType("int(11)");

                entity.Property(e => e.Role)
                    .IsRequired()
                    .HasColumnType("varchar(50)");

                entity.Property(e => e.UId)
                    .IsRequired()
                    .HasColumnName("uID")
                    .HasColumnType("varchar(8)");

                entity.HasOne(d => d.U)
                    .WithMany(p => p.Administrators)
                    .HasForeignKey(d => d.UId)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("Administrators_ibfk_1");
            });

            modelBuilder.Entity<AssignmentCategories>(entity =>
            {
                entity.HasKey(e => e.CategoryId)
                    .HasName("PRIMARY");

                entity.HasIndex(e => new { e.ClassId, e.Name })
                    .HasName("ClassID")
                    .IsUnique();

                entity.Property(e => e.CategoryId)
                    .HasColumnName("CategoryID")
                    .HasColumnType("int(11)");

                entity.Property(e => e.ClassId)
                    .HasColumnName("ClassID")
                    .HasColumnType("int(11)");

                entity.Property(e => e.GradingWeight).HasColumnType("int(11)");

                entity.Property(e => e.Name)
                    .IsRequired()
                    .HasColumnType("varchar(100)");

                entity.HasOne(d => d.Class)
                    .WithMany(p => p.AssignmentCategories)
                    .HasForeignKey(d => d.ClassId)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("AssignmentCategories_ibfk_1");
            });

            modelBuilder.Entity<Assignments>(entity =>
            {
                entity.HasKey(e => e.AssignmentId)
                    .HasName("PRIMARY");

                entity.HasIndex(e => new { e.Category, e.Name })
                    .HasName("Category")
                    .IsUnique();

                entity.Property(e => e.AssignmentId)
                    .HasColumnName("AssignmentID")
                    .HasColumnType("int(11)");

                entity.Property(e => e.Category).HasColumnType("int(11)");

                entity.Property(e => e.Contents)
                    .IsRequired()
                    .HasColumnType("text");

                entity.Property(e => e.DueDate).HasColumnType("datetime");

                entity.Property(e => e.MaxPointVal).HasColumnType("int(11)");

                entity.Property(e => e.Name)
                    .IsRequired()
                    .HasColumnType("varchar(100)");

                entity.HasOne(d => d.CategoryNavigation)
                    .WithMany(p => p.Assignments)
                    .HasForeignKey(d => d.Category)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("Assignments_ibfk_1");
            });

            modelBuilder.Entity<Classes>(entity =>
            {
                entity.HasKey(e => e.ClassId)
                    .HasName("PRIMARY");

                entity.HasIndex(e => e.Professor)
                    .HasName("Professor");

                entity.HasIndex(e => new { e.CatalogId, e.Semester })
                    .HasName("CatalogID")
                    .IsUnique();

                entity.Property(e => e.ClassId)
                    .HasColumnName("ClassID")
                    .HasColumnType("int(11)");

                entity.Property(e => e.CatalogId)
                    .IsRequired()
                    .HasColumnName("CatalogID")
                    .HasColumnType("varchar(5)");

                entity.Property(e => e.EndTime).HasColumnType("time");

                entity.Property(e => e.Location)
                    .IsRequired()
                    .HasColumnType("varchar(100)");

                entity.Property(e => e.Professor).HasColumnType("int(11)");

                entity.Property(e => e.Semester)
                    .IsRequired()
                    .HasColumnType("varchar(12)");

                entity.Property(e => e.StartTime).HasColumnType("time");

                entity.HasOne(d => d.Catalog)
                    .WithMany(p => p.Classes)
                    .HasForeignKey(d => d.CatalogId)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("Classes_ibfk_1");

                entity.HasOne(d => d.ProfessorNavigation)
                    .WithMany(p => p.Classes)
                    .HasForeignKey(d => d.Professor)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("Classes_ibfk_2");
            });

            modelBuilder.Entity<Courses>(entity =>
            {
                entity.HasKey(e => e.CatalogId)
                    .HasName("PRIMARY");

                entity.HasIndex(e => new { e.Dept, e.Number })
                    .HasName("Dept")
                    .IsUnique();

                entity.Property(e => e.CatalogId)
                    .HasColumnName("CatalogID")
                    .HasColumnType("varchar(5)");

                entity.Property(e => e.Dept)
                    .IsRequired()
                    .HasColumnType("varchar(4)");

                entity.Property(e => e.Name)
                    .IsRequired()
                    .HasColumnType("varchar(100)");

                entity.Property(e => e.Number)
                    .IsRequired()
                    .HasColumnType("varchar(4)");

                entity.HasOne(d => d.DeptNavigation)
                    .WithMany(p => p.Courses)
                    .HasForeignKey(d => d.Dept)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("Courses_ibfk_1");
            });

            modelBuilder.Entity<Departments>(entity =>
            {
                entity.HasKey(e => e.Dept)
                    .HasName("PRIMARY");

                entity.Property(e => e.Dept).HasColumnType("varchar(4)");

                entity.Property(e => e.Name)
                    .IsRequired()
                    .HasColumnType("varchar(100)");
            });

            modelBuilder.Entity<Enrollments>(entity =>
            {
                entity.HasKey(e => e.EnrollmentId)
                    .HasName("PRIMARY");

                entity.HasIndex(e => e.Class)
                    .HasName("Class");

                entity.HasIndex(e => e.Student)
                    .HasName("Student");

                entity.Property(e => e.EnrollmentId)
                    .HasColumnName("EnrollmentID")
                    .HasColumnType("int(11)");

                entity.Property(e => e.Class).HasColumnType("int(11)");

                entity.Property(e => e.Grade).HasColumnType("varchar(2)");

                entity.Property(e => e.Student).HasColumnType("int(11)");

                entity.HasOne(d => d.ClassNavigation)
                    .WithMany(p => p.Enrollments)
                    .HasForeignKey(d => d.Class)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("Enrollments_ibfk_2");

                entity.HasOne(d => d.StudentNavigation)
                    .WithMany(p => p.Enrollments)
                    .HasForeignKey(d => d.Student)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("Enrollments_ibfk_1");
            });

            modelBuilder.Entity<Professors>(entity =>
            {
                entity.HasKey(e => e.ProfessorId)
                    .HasName("PRIMARY");

                entity.HasIndex(e => e.Dept)
                    .HasName("Dept");

                entity.HasIndex(e => e.UId)
                    .HasName("uID");

                entity.Property(e => e.ProfessorId)
                    .HasColumnName("ProfessorID")
                    .HasColumnType("int(11)");

                entity.Property(e => e.Dept)
                    .IsRequired()
                    .HasColumnType("varchar(4)");

                entity.Property(e => e.UId)
                    .IsRequired()
                    .HasColumnName("uID")
                    .HasColumnType("varchar(8)");

                entity.HasOne(d => d.DeptNavigation)
                    .WithMany(p => p.Professors)
                    .HasForeignKey(d => d.Dept)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("Professors_ibfk_2");

                entity.HasOne(d => d.U)
                    .WithMany(p => p.Professors)
                    .HasForeignKey(d => d.UId)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("Professors_ibfk_1");
            });

            modelBuilder.Entity<Students>(entity =>
            {
                entity.HasKey(e => e.StudentId)
                    .HasName("PRIMARY");

                entity.HasIndex(e => e.Major)
                    .HasName("Major");

                entity.HasIndex(e => e.UId)
                    .HasName("uID");

                entity.Property(e => e.StudentId).HasColumnType("int(11)");

                entity.Property(e => e.Major)
                    .IsRequired()
                    .HasColumnType("varchar(4)");

                entity.Property(e => e.UId)
                    .IsRequired()
                    .HasColumnName("uID")
                    .HasColumnType("varchar(8)");

                entity.HasOne(d => d.MajorNavigation)
                    .WithMany(p => p.Students)
                    .HasForeignKey(d => d.Major)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("Students_ibfk_2");

                entity.HasOne(d => d.U)
                    .WithMany(p => p.Students)
                    .HasForeignKey(d => d.UId)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("Students_ibfk_1");
            });

            modelBuilder.Entity<Submissions>(entity =>
            {
                entity.HasKey(e => e.SubmissionId)
                    .HasName("PRIMARY");

                entity.HasIndex(e => e.Assignment)
                    .HasName("Assignment");

                entity.HasIndex(e => e.Student)
                    .HasName("Student");

                entity.Property(e => e.SubmissionId)
                    .HasColumnName("SubmissionID")
                    .HasColumnType("int(11)");

                entity.Property(e => e.Assignment).HasColumnType("int(11)");

                entity.Property(e => e.Contents).HasColumnType("text");

                entity.Property(e => e.Score).HasColumnType("int(11)");

                entity.Property(e => e.Student).HasColumnType("int(11)");

                entity.Property(e => e.Time).HasColumnType("datetime");

                entity.HasOne(d => d.AssignmentNavigation)
                    .WithMany(p => p.Submissions)
                    .HasForeignKey(d => d.Assignment)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("Submissions_ibfk_2");

                entity.HasOne(d => d.StudentNavigation)
                    .WithMany(p => p.Submissions)
                    .HasForeignKey(d => d.Student)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("Submissions_ibfk_1");
            });

            modelBuilder.Entity<Users>(entity =>
            {
                entity.HasKey(e => e.UId)
                    .HasName("PRIMARY");

                entity.Property(e => e.UId)
                    .HasColumnName("uID")
                    .HasColumnType("varchar(8)");

                entity.Property(e => e.Dob)
                    .HasColumnName("DOB")
                    .HasColumnType("date");

                entity.Property(e => e.FirstName)
                    .IsRequired()
                    .HasColumnType("varchar(100)");

                entity.Property(e => e.LastName)
                    .IsRequired()
                    .HasColumnType("varchar(100)");
            });
        }
    }
}
